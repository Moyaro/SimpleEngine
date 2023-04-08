#include "render_pipeline_base.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/function/global/global_context.h"
#include "render_resource.h"
#include "render_resource_base.h"

namespace SimpleEngine {
    void RenderPipelineBase::preparePassData(std::shared_ptr<RenderResourceBase> render_resource){
        m_main_camera_pass->preparePassData(render_resource);
        m_pick_pass->preparePassData(render_resource);
        m_directional_light_pass->preparePassData(render_resource);
        m_point_light_shadow_pass->preparePassData(render_resource);
        g_runtime_global_context.m_debugdraw_manager->preparePassData(render_resource);
    }
}