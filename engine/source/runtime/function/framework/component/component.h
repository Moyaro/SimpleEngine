#pragma once
#include "runtime/core/meta/reflection/reflection.h"

namespace SimpleEngine
{
    class GObject;
    // Component
    REFLECTION_TYPE(Component)
        CLASS(Component, WhiteListFields)
    {
        REFLECTION_BODY(Component)
    protected:
        std::weak_ptr<GObject> m_parent_object;
        bool m_is_dirty{ false };
        bool m_is_scale_dirty{ false };

    public:
        Component() = default;
        virtual ~Component() {}

        //组件资源加载后设置进属性：每个组件都要挂载到物体上
        virtual void postLoadResource(std::weak_ptr<GObject> parent_object) { m_parent_object = parent_object; }

        virtual void tick(float delta_time) {};

        //dirty：刚体组件需要被更新
        bool isDirty() const { return m_is_dirty; }
        void setDirtyFlag(bool is_dirty) { m_is_dirty = is_dirty; }

        bool m_tick_in_editor_mode{ false };
    };

}