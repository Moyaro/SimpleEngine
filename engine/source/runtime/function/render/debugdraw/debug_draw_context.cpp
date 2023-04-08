#include "debug_draw_context.h"

namespace SimpleEngine {
    DebugDrawGroup* DebugDrawContext::tryGetOrCreateDebugDrawGroup(const std::string& name)
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        //���Ŀǰ�е�group���Ƿ���ͬ������ֱ�ӷ���
        size_t debug_draw_group_count = m_debug_draw_groups.size();
        for (size_t index = 0; index < debug_draw_group_count; index++)
        {
            DebugDrawGroup* debug_draw_group = m_debug_draw_groups[index];
            if (debug_draw_group->getName() == name)
            {
                return debug_draw_group;
            }
        }

        //û�У��ø�name����һ����group
        DebugDrawGroup* new_debug_draw_group = new DebugDrawGroup;
        new_debug_draw_group->setName(name);
        m_debug_draw_groups.push_back(new_debug_draw_group);

        return new_debug_draw_group;
    }

    
    void DebugDrawContext::clear()
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        //����ָ������������
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

        //���������������Ƿ��������ڽ������������Ƴ�
        size_t debug_draw_group_count = m_debug_draw_groups.size();
        for (size_t index = 0; index < debug_draw_group_count; index++)
        {
            if (m_debug_draw_groups[index] == nullptr)continue;
            m_debug_draw_groups[index]->removeDeadPrimitives(delta_time);
        }
    }
}