#pragma once

#include "runtime/resource/res_type/common/world.h"

#include <filesystem>
#include <string>

namespace SimpleEngine
{
    class Level;
    class LevelDebugger;

    /// 管理世界：编辑/游戏世界
    /// 目前仅能管理一个世界和关卡
    class WorldManager
    {
    public:
        virtual ~WorldManager();
        void clear();//清理所有关卡、世界，并把世界加载状态设置为false

        void init();//设置世界加载状态，url，level_debugger
        
        void reloadCurrentLevel();
        void saveCurrentLevel();//调用level的函数保存关卡

        void                 tick(float delta_time);
        std::weak_ptr<Level> getCurrentActiveLevel() const { return m_current_active_level; }

    private:
        bool loadWorld(const std::string& world_url);
        bool loadLevel(const std::string& level_url);

        bool                      m_is_world_loaded{ false };
        std::string               m_current_world_url;
        std::shared_ptr<WorldRes> m_current_world_resource;

        //key: 关卡地址, vaule: 关卡实例
        std::unordered_map<std::string, std::shared_ptr<Level>> m_loaded_levels;

        //激活的关卡，目前只支持一个
        std::weak_ptr<Level> m_current_active_level;

        //debug level
        std::shared_ptr<LevelDebugger> m_level_debugger;
    };
}