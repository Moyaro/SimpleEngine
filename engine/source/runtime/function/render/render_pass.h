#pragma once

#include "runtime/function/render/render_common.h"
#include "runtime/function/render/render_pass_base.h"
#include "runtime/function/render/render_resource.h"

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace SimpleEngine
{
    class VulkanRHI;

    enum
    {
        _main_camera_pass_gbuffer_a                     = 0,
        _main_camera_pass_gbuffer_b                     = 1,
        _main_camera_pass_gbuffer_c                     = 2,
        _main_camera_pass_backup_buffer_odd             = 3,
        _main_camera_pass_backup_buffer_even            = 4,
        _main_camera_pass_post_process_buffer_odd       = 5,
        _main_camera_pass_post_process_buffer_even      = 6,
        _main_camera_pass_depth                         = 7,
        _main_camera_pass_swap_chain_image              = 8,
        _main_camera_pass_custom_attachment_count       = 5,
        _main_camera_pass_post_process_attachment_count = 2,
        _main_camera_pass_attachment_count              = 9,
    };

    //子流程数量
    enum
    {
        _main_camera_subpass_basepass = 0,
        _main_camera_subpass_deferred_lighting,
        _main_camera_subpass_forward_lighting,
        _main_camera_subpass_ui,
        _main_camera_subpass_combine_ui,
        _main_camera_subpass_count
    };

    struct VisiableNodes
    {
        std::vector<RenderMeshNode>* p_directional_light_visible_mesh_nodes{ nullptr };
        std::vector<RenderMeshNode>* p_point_lights_visible_mesh_nodes{ nullptr };
        std::vector<RenderMeshNode>* p_main_camera_visible_mesh_nodes{ nullptr };
        RenderAxisNode* p_axis_node{ nullptr };
    };

    class RenderPass : public RenderPassBase
    {
    public:
        //帧缓冲附件
        struct FrameBufferAttachment
        {
            VkImage image;
            VkDeviceMemory mem;
            VkImageView view;
            VkFormat format;
        };

        //帧缓冲
        struct Framebuffer
        {
            int width;
            int height;
            VkFramebuffer framebuffer;
            VkRenderPass render_pass;

            std::vector<FrameBufferAttachment> attachments;
        };

        //描述符集
        struct Descriptor
        {
            VkDescriptorSetLayout layout;
            VkDescriptorSet descriptor_set;
        };

        //管线
        struct RenderPipelineBase
        {
            VkPipelineLayout layout;
            VkPipeline pipeline;
        };

        std::vector<Descriptor> m_descriptor_infos;
        std::vector<RenderPipelineBase> m_render_pipelines;
        Framebuffer m_framebuffer;

        void init(const RenderPassInitInfo* init_info) override;//获取全局渲染资源
        void postInitialize() override{}

        virtual void draw(){}

        virtual VkRenderPass& getRenderPass() { return m_framebuffer.render_pass; }
        virtual std::vector<VkImageView> getFramebufferImageViews() const;
        virtual std::vector<VkDescriptorSetLayout> getDescriptorSetLayouts() const;

        static VisiableNodes m_visiable_nodes;
        GlobalRenderResource* m_global_render_resource{ nullptr };
    };
}