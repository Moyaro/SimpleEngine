#include "render_pipeline.h"
#include "../global/global_context.h"
#include "debugdraw/debug_draw_manager.h"
#include "interface/vulkan_rhi.h"
#include "render_resource_base.h"

#include "runtime/function/render/passes/main_camera_pass.h"
#include "runtime/function/render/passes/pick_pass.h"
#include "runtime/function/render/passes/ui_pass.h"
#include "runtime/function/render/passes/point_light_pass.h"
#include "runtime/function/render/passes/directional_light_pass.h"
#include "runtime/function/render/passes/combine_ui_pass.h"

namespace SimpleEngine {
    void RenderPipeline::init(RenderPipelineInitInfo init_info)
    {
        m_point_light_shadow_pass = std::make_shared<PointLightShadowPass>();
        m_directional_light_pass = std::make_shared<DirectionalLightShadowPass>();
        m_main_camera_pass = std::make_shared<MainCameraPass>();
        m_ui_pass = std::make_shared<UIPass>();
        m_combine_ui_pass = std::make_shared<CombineUIPass>();
        m_pick_pass = std::make_shared<PickPass>();

        RenderPassCommonInfo pass_common_info;
        pass_common_info.rhi = m_rhi;
        pass_common_info.render_resource = init_info.render_resource;

        m_point_light_shadow_pass->setCommonInfo(pass_common_info);
        m_directional_light_pass->setCommonInfo(pass_common_info);
        m_main_camera_pass->setCommonInfo(pass_common_info);
        m_ui_pass->setCommonInfo(pass_common_info);
        m_combine_ui_pass->setCommonInfo(pass_common_info);
        m_pick_pass->setCommonInfo(pass_common_info);

        m_point_light_shadow_pass->init(nullptr);
        m_directional_light_pass->init(nullptr);

        std::shared_ptr<MainCameraPass> main_camera_pass = std::static_pointer_cast<MainCameraPass>(m_main_camera_pass);
        std::shared_ptr<RenderPass>     _main_camera_pass = std::static_pointer_cast<RenderPass>(m_main_camera_pass);

        main_camera_pass->m_point_light_shadow_color_image_view =
            std::static_pointer_cast<RenderPass>(m_point_light_shadow_pass)->getFramebufferImageViews()[0];
        main_camera_pass->m_directional_light_shadow_color_image_view =
            std::static_pointer_cast<RenderPass>(m_directional_light_pass)->m_framebuffer.attachments[0].view;

        MainCameraPassInitInfo main_camera_init_info;
        m_main_camera_pass->init(&main_camera_init_info);

        std::vector<VkDescriptorSetLayout> descriptor_layouts = _main_camera_pass->getDescriptorSetLayouts();
        std::static_pointer_cast<PointLightShadowPass>(m_point_light_shadow_pass) ->setPerMeshLayout(descriptor_layouts[MainCameraPass::LayoutType::_per_mesh]);
        std::static_pointer_cast<DirectionalLightShadowPass>(m_directional_light_pass) ->setPerMeshLayout(descriptor_layouts[MainCameraPass::LayoutType::_per_mesh]);

        m_point_light_shadow_pass->postInitialize();
        m_directional_light_pass->postInitialize();

        UIPassInitInfo ui_init_info;
        ui_init_info.render_pass = _main_camera_pass->getRenderPass();
        m_ui_pass->init(&ui_init_info);

        CombineUIPassInitInfo combine_ui_init_info;
        combine_ui_init_info.render_pass = _main_camera_pass->getRenderPass();
        combine_ui_init_info.scene_input_attachment = _main_camera_pass->getFramebufferImageViews()[_main_camera_pass_backup_buffer_odd];
        combine_ui_init_info.ui_input_attachment = _main_camera_pass->getFramebufferImageViews()[_main_camera_pass_backup_buffer_even];
        m_combine_ui_pass->init(&combine_ui_init_info);

        PickPassInitInfo pick_init_info;
        pick_init_info.per_mesh_layout = descriptor_layouts[MainCameraPass::LayoutType::_per_mesh];
        m_pick_pass->init(&pick_init_info);

    }

    void RenderPipeline::forwardRender(std::shared_ptr<RenderResourceBase> render_resource)
    {
        VulkanRHI* vulkan_rhi = static_cast<VulkanRHI*>(m_rhi.get());
        RenderResource* vulkan_resource = static_cast<RenderResource*>(render_resource.get());
        vulkan_resource->resetRingBufferOffset(vulkan_rhi->m_current_frame_index);
        vulkan_rhi->waitForFences();//等待当前帧结束渲染
        m_rhi->resetCommandPool();

        if (vulkan_rhi->prepareBeforePass(std::bind(&RenderPipeline::passUpdateAfterRecreateSwapchain, this)))
            return;

        static_cast<DirectionalLightShadowPass*>(m_directional_light_pass.get())->draw();

        static_cast<PointLightShadowPass*>(m_point_light_shadow_pass.get())->draw();

        UIPass& ui_pass = *(static_cast<UIPass*>(m_ui_pass.get()));
        CombineUIPass& combine_ui_pass = *(static_cast<CombineUIPass*>(m_combine_ui_pass.get()));
        static_cast<MainCameraPass*>(m_main_camera_pass.get())
            ->drawForward(ui_pass, combine_ui_pass, vulkan_rhi->m_current_swapchain_image_index);

        g_runtime_global_context.m_debugdraw_manager->draw(vulkan_rhi->m_current_swapchain_image_index);

        vulkan_rhi->submitRendering(std::bind(&RenderPipeline::passUpdateAfterRecreateSwapchain, this));
    }

    void RenderPipeline::passUpdateAfterRecreateSwapchain()
    {
        MainCameraPass& main_camera_pass = *(static_cast<MainCameraPass*>(m_main_camera_pass.get()));
        PickPass& pick_pass = *(static_cast<PickPass*>(m_pick_pass.get()));
        CombineUIPass&  combine_ui_pass  = *(static_cast<CombineUIPass*>(m_combine_ui_pass.get()));

        main_camera_pass.updateAfterFramebufferRecreate();
        combine_ui_pass.updateAfterFramebufferRecreate(
            main_camera_pass.getFramebufferImageViews()[_main_camera_pass_backup_buffer_odd],
            main_camera_pass.getFramebufferImageViews()[_main_camera_pass_backup_buffer_even]);
        pick_pass.recreateFramebuffer();
        g_runtime_global_context.m_debugdraw_manager->updateAfterRecreateSwapchain();
    }

    uint32_t RenderPipeline::getGuidOfPickedMesh(const Vector2& picked_uv)
    {
        PickPass& pick_pass = *(static_cast<PickPass*>(m_pick_pass.get()));
        return pick_pass.pick(picked_uv);
    }

    void RenderPipeline::setAxisVisibleState(bool state)
    {
        MainCameraPass& main_camera_pass = *(static_cast<MainCameraPass*>(m_main_camera_pass.get()));
        main_camera_pass.m_is_show_axis = state;//轴可见/不可见
    }

    void RenderPipeline::setSelectedAxis(size_t selected_axis)
    {
        MainCameraPass& main_camera_pass = *(static_cast<MainCameraPass*>(m_main_camera_pass.get()));
        main_camera_pass.m_selected_axis = selected_axis;
    }
}