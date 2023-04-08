#pragma once
#include <memory>
#include "interface/rhi.h"
#include "runtime/core/math/vector2.h"
#include "runtime/function/render/render_pass_base.h"

#include <memory>
#include <vector>

namespace SimpleEngine {

    class RHI;
    class WindowUI;

    struct RenderPipelineInitInfo
    {
        std::shared_ptr<RenderResourceBase> render_resource;
    };

    class RenderPipelineBase
    {
        friend class RenderSystem;

    public:
        virtual ~RenderPipelineBase() {}
        virtual void clear(){}
        virtual void init(RenderPipelineInitInfo init_info) = 0;

        virtual void preparePassData(std::shared_ptr<RenderResourceBase> render_resource);//准备流程数据
        virtual void forwardRender(std::shared_ptr<RenderResourceBase> render_resource){}

        void initializeUIRenderBackend(WindowUI* window_ui) { m_ui_pass->initializeUIRenderBackend(window_ui); }
        virtual uint32_t getGuidOfPickedMesh(const Vector2& picked_uv) = 0;

    protected:
        std::shared_ptr<RHI> m_rhi;

        std::shared_ptr<RenderPassBase> m_directional_light_pass;
        std::shared_ptr<RenderPassBase> m_point_light_shadow_pass;
        std::shared_ptr<RenderPassBase> m_main_camera_pass;
        std::shared_ptr<RenderPassBase> m_ui_pass;
        std::shared_ptr<RenderPassBase> m_pick_pass;
    };
}