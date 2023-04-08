#include "runtime/function/render/render_pass.h"
#include "runtime/function/render/render_resource.h"
#include "runtime/function/render/interface/vulkan_rhi.h"

SimpleEngine::VisiableNodes SimpleEngine::RenderPass::m_visiable_nodes;

namespace SimpleEngine
{
    void RenderPass::init(const RenderPassInitInfo* init_info)
    {
        m_global_render_resource = &(std::static_pointer_cast<RenderResource>(m_render_resource)->m_global_render_resource);
    }

    std::vector<VkImageView> RenderPass::getFramebufferImageViews() const
    {
        std::vector<VkImageView> image_views;
        for (auto& attach : m_framebuffer.attachments)
        {
            image_views.push_back(attach.view);
        }
        return image_views;
    }

    std::vector<VkDescriptorSetLayout> RenderPass::getDescriptorSetLayouts() const
    {
        std::vector<VkDescriptorSetLayout> layouts;
        for (auto& desc : m_descriptor_infos)
        {
            layouts.push_back(desc.layout);
        }
        return layouts;
    }
}