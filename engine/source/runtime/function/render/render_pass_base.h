#pragma once
#include "runtime/function/render/interface/rhi.h"
namespace SimpleEngine
{
    class RHI;
    class RenderResourceBase;
    class WindowUI;

    struct RenderPassInitInfo
    {};

    struct RenderPassCommonInfo
    {
        std::shared_ptr<RHI> rhi;
        std::shared_ptr<RenderResourceBase> render_resource;
    };

    class RenderPassBase
    {
    public:
        virtual void init(const RenderPassInitInfo* init_info) = 0;
        virtual void postInitialize(){}
        virtual void setCommonInfo(RenderPassCommonInfo common_info) { m_render_resource = common_info.render_resource; m_rhi = common_info.rhi; }
        virtual void preparePassData(std::shared_ptr<RenderResourceBase> render_resource){}
        virtual void initializeUIRenderBackend(WindowUI* window_ui){}

    protected:
        std::shared_ptr<RHI> m_rhi;
        std::shared_ptr<RenderResourceBase> m_render_resource;
    };
}