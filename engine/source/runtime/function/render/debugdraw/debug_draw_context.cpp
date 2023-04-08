#include "debug_draw_context.h"

namespace SimpleEngine {
    DebugDrawGroup* DebugDrawContext::tryGetOrCreateDebugDrawGroup(const std::string& name)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        //检查目前有的group里是否有同名，有直接返回
        size_t debug_draw_group_count = m_debug_draw_groups.size();
        for (size_t index = 0; index < debug_draw_group_count; index++)
        {
            DebugDrawGroup* debug_draw_group = m_debug_draw_groups[index];
            if (debug_draw_group->getName() == name)
            {
                return debug_draw_group;
            }
        }

        //没有，用该name创建一个新group
        DebugDrawGroup* new_debug_draw_group = new DebugDrawGroup;
        new_debug_draw_group->setName(name);
        m_debug_draw_groups.push_back(new_debug_draw_group);

        return new_debug_draw_group;
    }

    
    void DebugDrawContext::clear()
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        //清理指针完了清整体
        size_t debug_draw_group_count = m_debug_draw_groups.size();
        for (size_t index = 0; index < debug_draw_group_count; index++)
        {
            delete m_debug_draw_groups[index];
        }

        m_debug_draw_groups.clear();
    }

    void DebugDrawContext::removeDeadPrimitives(float delta_time)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        //让所有物体组检查是否生命周期结束，结束则移除
        size_t debug_draw_group_count = m_debug_draw_groups.size();
        for (size_t index = 0; index < debug_draw_group_count; index++)
        {
            if (m_debug_draw_groups[index] == nullptr)continue;
            m_debug_draw_groups[index]->removeDeadPrimitives(delta_time);
        }
    }
}