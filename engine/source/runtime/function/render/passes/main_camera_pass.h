#pragma once

#include "runtime/function/render/render_pass.h"
#include "runtime/function/render/passes/ui_pass.h"

namespace SimpleEngine
{
    class RenderResourceBase;

    struct MainCameraPassInitInfo : RenderPassInitInfo
    {
    };

    class MainCameraPass : public RenderPass
    {
    public:
       //布局类型
        enum LayoutType : uint8_t
        {
            _per_mesh = 0,
            _mesh_global,
            _mesh_per_material,
            _skybox,
            _axis,
            _deferred_lighting,
            _layout_type_count
        };

        //管线类型
        enum RenderPipeLineType : uint8_t
        {
            _render_pipeline_type_mesh_gbuffer = 0,
            _render_pipeline_type_deferred_lighting,
            _render_pipeline_type_mesh_lighting,
            _render_pipeline_type_skybox,
            _render_pipeline_type_axis,
            _render_pipeline_type_count
        };

        void init(const RenderPassInitInfo* init_info) override final;

        void preparePassData(std::shared_ptr<RenderResourceBase> render_resource) override final;

        void drawForward(UIPass& ui_pass,uint32_t current_swapchain_image_index);

        void copyNormalAndDepthImage();

        VkImageView m_point_light_shadow_color_image_view;
        VkImageView m_directional_light_shadow_color_image_view;
        bool m_is_show_axis{ false };
        size_t m_selected_axis{ 3 };
        MeshPerframeStorageBufferObject m_mesh_perframe_storage_buffer_object;
        AxisStorageBufferObject m_axis_storage_buffer_object;

        void updateAfterFramebufferRecreate();

        VkCommandBuffer getRenderCommandBuffer();

    private:
        void setupAttachments();
        void setupRenderPass();
        void setupDescriptorSetLayout();
        void setupPipelines();
        void setupDescriptorSet();
        void setupFramebufferDescriptorSet();
        void setupSwapchainFramebuffers();

        void setupSkyboxDescriptorSet();
        void setupModelGlobalDescriptorSet();
        void setupAxisDescriptorSet();
        void setupGbufferLightingDescriptorSet();

        void drawMeshGbuffer();
        void drawDeferredLighting();
        void drawMeshLighting();
        void drawSkybox();
        void drawAxis();

        std::vector<VkFramebuffer> m_swapchain_framebuffers;
    };
}