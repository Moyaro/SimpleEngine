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
    /// game object�Ļ�����
    /// </summary>
    class GObject : public std::enable_shared_from_this<GObject>
    {
    public:
        GObject(GObjectID id) : m_id{ id } {}
        virtual ~GObject();//ɾ����ָ��

        virtual void tick(float delta_time);//�������Ƿ���Ҫtick

        //��ȡ/������res
        bool load(const ObjectInstanceRes& object_instance_res);
        void save(ObjectInstanceRes& out_object_instance_res);

        GObjectID getID() const { return m_id; }

        //������
        void  setName(std::string name) { m_name = name; }
        const std::string& getName() const { return m_name; }

        bool hasComponent(const std::string& compenent_type_name) const;//��������������Ƿ������
        std::vector<Reflection::ReflectionPtr<Component>> getComponents() { return m_components; }//��ȡ���

        //������������ȡ���
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
        //���û�ȡ����ķ���
#define tryGetComponent(COMPONENT_TYPE) tryGetComponent<COMPONENT_TYPE>(#COMPONENT_TYPE)
#define tryGetComponentConst(COMPONENT_TYPE) tryGetComponentConst<const COMPONENT_TYPE>(#COMPONENT_TYPE)

    protected:
        GObjectID   m_id{ k_invalid_gobject_id };
        std::string m_name;
        std::string m_definition_url;

        //��ReflectionPtr��ԭ���������Ҫ����
        // in editor, and it's polymorphism
        std::vector<Reflection::ReflectionPtr<Component>> m_components;
    };
}