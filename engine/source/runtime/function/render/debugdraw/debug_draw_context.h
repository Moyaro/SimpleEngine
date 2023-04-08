#pragma once

#include "debug_draw_group.h"
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// 管理图形组的生命周期
    /// </summary>
    class DebugDrawContext
    {
    public:
        DebugDrawGroup* tryGetOrCreateDebugDrawGroup(const std::string& name);//创建新的组
        void clear();//删除所有组
        void tick(float delta_time) { removeDeadPrimitives(delta_time); }//每帧检查是否有组需要移除

        std::vector<DebugDrawGroup*> m_debug_draw_groups;//所有组
    private:
        std::mutex m_mutex;
        void removeDeadPrimitives(float delta_time);
    };
}