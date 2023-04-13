#pragma once

#include "runtime/resource/res_type/common/world.h"

#include <filesystem>
#include <string>

namespace SimpleEngine
{
    class Level;
    class LevelDebugger;

    /// �������磺�༭/��Ϸ����
    /// Ŀǰ���ܹ���һ������͹ؿ�
    class WorldManager
    {
    public:
        virtual ~WorldManager();
        void clear();//�������йؿ������磬�����������״̬����Ϊfalse

        void init();//�����������״̬��url��level_debugger
        
        void reloadCurrentLevel();
        void saveCurrentLevel();//����level�ĺ�������ؿ�

        void                 tick(float delta_time);
        std::weak_ptr<Level> getCurrentActiveLevel() const { return m_current_active_level; }

    private:
        bool loadWorld(const std::string& world_url);
        bool loadLevel(const std::string& level_url);

        bool                      m_is_world_loaded{ false };
        std::string               m_current_world_url;
        std::shared_ptr<WorldRes> m_current_world_resource;

        //key: �ؿ���ַ, vaule: �ؿ�ʵ��
        std::unordered_map<std::string, std::shared_ptr<Level>> m_loaded_levels;

        //����Ĺؿ���Ŀǰֻ֧��һ��
        std::weak_ptr<Level> m_current_active_level;

        //debug level
        std::shared_ptr<LevelDebugger> m_level_debugger;
    };
}