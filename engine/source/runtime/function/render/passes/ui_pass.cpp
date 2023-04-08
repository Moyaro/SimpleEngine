#include "runtime/function/render/passes/ui_pass.h"

#include "runtime/function/render/interface/vulkan_rhi.h"

#include "runtime/resource/config_manager/config_manager.h"

#include "runtime/function/ui/window_ui.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

namespace SimpleEngine
{
    void UIPass::init(const RenderPassInitInfo* init_info)
    {
        RenderPass::init(nullptr);

        m_framebuffer.render_pass = static_cast<const UIPassInitInfo*>(init_info)->render_pass;
    }

    void UIPass::initializeUIRenderBackend(WindowUI* window_ui)
    {
        m_window_ui = window_ui;

        ImGui_ImplGlfw_InitForVulkan(std::static_pointer_cast<VulkanRHI>(m_rhi)->m_window, true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_instance;
        init_info.PhysicalDevice = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_physical_device;
        init_info.Device = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_device;
        init_info.QueueFamily = m_rhi->getQueueFamilyIndices().graphics_family.value();
        init_info.Queue = m_rhi->getGraphicsQueue();
        init_info.DescriptorPool = std::static_pointer_cast<VulkanRHI>(m_rhi)->m_descriptor_pool;
        init_info.Subpass = _main_camera_subpass_ui;

        // may be different from the real swapchain image count
        // see ImGui_ImplVulkanH_GetMinImageCountFromPresentMode
        init_info.MinImageCount = 3;
        init_info.ImageCount = 3;
        ImGui_ImplVulkan_Init(&init_info, m_framebuffer.render_pass);

        uploadFonts();
    }

    void UIPass::uploadFonts()
    {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = m_rhi->getCommandPool();
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        if (VK_SUCCESS != m_rhi->allocateCommandBuffers(&allocInfo, &commandBuffer))
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        if (VK_SUCCESS != m_rhi->beginCommandBuffer(commandBuffer, &beginInfo))
        {
            throw std::runtime_error("Could not create one-time command buffer!");
        }

        ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);

        if (VK_SUCCESS != m_rhi->endCommandBuffer(commandBuffer))
        {
            throw std::runtime_error("failed to record command buffer!");
        }

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        m_rhi->queueSubmit(m_rhi->getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        m_rhi->queueWaitIdle(m_rhi->getGraphicsQueue());

        VkCommandPool commandPool = m_rhi->getCommandPool();
        m_rhi->freeCommandBuffers(commandPool, 1, &commandBuffer);

        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    void UIPass::draw()
    {
        if (m_window_ui)
        {
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            m_window_ui->preRender();

            ImGui::Render();

            ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), std::static_pointer_cast<VulkanRHI>(m_rhi)->m_current_command_buffer);
        }
    }
}