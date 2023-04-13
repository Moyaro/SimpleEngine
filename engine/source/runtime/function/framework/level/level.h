#pragma once

#include "runtime/function/framework/object/object_id_allocator.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace SimpleEngine
{
    class GObject;
    class ObjectInstanceRes;

    using LevelObjectsMap = std::unordered_map<GObjectID, std::shared_ptr<GObject>>;

    /// <summary>
    /// �������йؿ���GO
    /// </summary>
    class Level
    {
    public:
        virtual ~Level() {};

        bool load(const std::string& level_res_url);
        void unload();//�˳��ؿ�ʹ����

        bool save();

        void tick(float delta_time);//�ؿ�������tick

        const std::string& getLevelResUrl() const { return m_level_res_url; }//��ȡlevel��ַ

        //��ȡGO
        const LevelObjectsMap& getAllGObjects() const { return m_gobjects; }
        std::weak_ptr<GObject>   getGObjectByID(GObjectID go_id) const;
        //����GO
        GObjectID createObject(const ObjectInstanceRes& object_instance_res);
        //ɾ��GO
        void      deleteGObjectByID(GObjectID go_id);

        std::shared_ptr<GObject> getCameraObject() { return m_cameraObject;};//��ȡ���

    protected:
        void clear();

        bool        m_is_loaded{ false };
        std::string m_level_res_url;

        std::shared_ptr<GObject> m_cameraObject = nullptr;

        //key: ����id, value:����ʵ��ָ��
        LevelObjectsMap m_gobjects;
    };
}