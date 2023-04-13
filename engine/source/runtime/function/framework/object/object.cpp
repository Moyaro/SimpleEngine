#include "runtime/function/framework/object/object.h"

#include "runtime/engine.h"

#include "runtime/core/meta/reflection/reflection.h"

#include "runtime/resource/asset_manager/asset_manager.h"

#include "runtime/function/framework/component/component.h"
#include "runtime/function/framework/component/transform/transform_component.h"
#include "runtime/function/global/global_context.h"

#include <cassert>
#include <unordered_set>

#include "_generated/serializer/all_serializer.h"

namespace SimpleEngine
{

    GObject::~GObject()
    {
        for (auto& component : m_components)
        {
            ENGINE_REFLECTION_DELETE(component);
        }
        m_components.clear();
    }

    bool shouldComponentTick(std::string component_type_name)
    {
        if (g_is_editor_mode)//检查编辑模式该组件类型是否需要tick
        {
            return g_editor_tick_component_types.find(component_type_name) != g_editor_tick_component_types.end();
        }
        else
        {
            return true;
        }
    }
    void GObject::tick(float delta_time)
    {
        for (auto& component : m_components)//检查组件是否需要tick
        {
            if (shouldComponentTick(component.getTypeName()))
            {
                component->tick(delta_time);
            }
        }
    }

    bool GObject::hasComponent(const std::string& compenent_type_name) const
    {
        for (const auto& component : m_components)
        {
            if (component.getTypeName() == compenent_type_name)
                return true;
        }

        return false;
    }

    bool GObject::load(const ObjectInstanceRes& object_instance_res)
    {
        //清理旧组件
        m_components.clear();

        setName(object_instance_res.m_name);//设置名称

        //从资源中获取内容
        m_components = object_instance_res.m_instanced_components;//获取已实例化的组件
        for (auto component : m_components)
        {
            if (component)
            {
                component->postLoadResource(weak_from_this());
            }
        }

        //读取物体定义资源
        m_definition_url = object_instance_res.m_definition;
        ObjectDefinitionRes definition_res;
        const bool is_loaded_success = g_runtime_global_context.m_asset_manager->loadAsset(m_definition_url, definition_res);
        if (!is_loaded_success)
            return false;

        for (auto loaded_component : definition_res.m_components)
        {
            const std::string type_name = loaded_component.getTypeName();

            //如果已实例化就跳过
            if (hasComponent(type_name))
                continue;

            //未实例化就加载资源、放入m_components中
            loaded_component->postLoadResource(weak_from_this());
            m_components.push_back(loaded_component);
        }

        return true;
    }

    void GObject::save(ObjectInstanceRes& out_object_instance_res)
    {
        out_object_instance_res.m_name = m_name;
        out_object_instance_res.m_definition = m_definition_url;
        out_object_instance_res.m_instanced_components = m_components;
    }

}