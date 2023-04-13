#pragma once

#include "runtime/function/framework/component/component.h"
#include "runtime/function/framework/object/object_id_allocator.h"

#include "runtime/resource/res_type/common/object.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace SimpleEngine
{
    /// <summary>
    /// game object的基础类
    /// </summary>
    class GObject : public std::enable_shared_from_this<GObject>
    {
    public:
        GObject(GObjectID id) : m_id{ id } {}
        virtual ~GObject();//删反射指针

        virtual void tick(float delta_time);//检查组件是否需要tick

        //读取/保存至res
        bool load(const ObjectInstanceRes& object_instance_res);
        void save(ObjectInstanceRes& out_object_instance_res);

        GObjectID getID() const { return m_id; }

        //物体名
        void  setName(std::string name) { m_name = name; }
        const std::string& getName() const { return m_name; }

        bool hasComponent(const std::string& compenent_type_name) const;//根据类型名检查是否有组件
        std::vector<Reflection::ReflectionPtr<Component>> getComponents() { return m_components; }//获取组件

        //根据类型名获取组件
        template<typename TComponent>
        TComponent* tryGetComponent(const std::string& compenent_type_name)
        {
            for (auto& component : m_components)
            {
                if (component.getTypeName() == compenent_type_name)
                {
                    return static_cast<TComponent*>(component.operator->());
                }
            }

            return nullptr;
        }
        template<typename TComponent>
        const TComponent* tryGetComponentConst(const std::string& compenent_type_name) const
        {
            for (const auto& component : m_components)
            {
                if (component.getTypeName() == compenent_type_name)
                {
                    return static_cast<const TComponent*>(component.operator->());
                }
            }
            return nullptr;
        }
        //调用获取组件的方法
#define tryGetComponent(COMPONENT_TYPE) tryGetComponent<COMPONENT_TYPE>(#COMPONENT_TYPE)
#define tryGetComponentConst(COMPONENT_TYPE) tryGetComponentConst<const COMPONENT_TYPE>(#COMPONENT_TYPE)

    protected:
        GObjectID   m_id{ k_invalid_gobject_id };
        std::string m_name;
        std::string m_definition_url;

        //用ReflectionPtr的原因是组件需要反射
        // in editor, and it's polymorphism
        std::vector<Reflection::ReflectionPtr<Component>> m_components;
    };
}