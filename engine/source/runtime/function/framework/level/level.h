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
    /// 管理所有关卡内GO
    /// </summary>
    class Level
    {
    public:
        virtual ~Level() {};

        bool load(const std::string& level_res_url);
        void unload();//退出关卡使调用

        bool save();

        void tick(float delta_time);//关卡内物体tick

        const std::string& getLevelResUrl() const { return m_level_res_url; }//获取level地址

        //获取GO
        const LevelObjectsMap& getAllGObjects() const { return m_gobjects; }
        std::weak_ptr<GObject>   getGObjectByID(GObjectID go_id) const;
        //创建GO
        GObjectID createObject(const ObjectInstanceRes& object_instance_res);
        //删除GO
        void      deleteGObjectByID(GObjectID go_id);

        std::shared_ptr<GObject> getCameraObject() { return m_cameraObject;};//获取相机

    protected:
        void clear();

        bool        m_is_loaded{ false };
        std::string m_level_res_url;

        std::shared_ptr<GObject> m_cameraObject = nullptr;

        //key: 物体id, value:物体实例指针
        LevelObjectsMap m_gobjects;
    };
}