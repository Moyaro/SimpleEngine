#pragma once

#include "debug_draw_group.h"
#include <vector>

namespace SimpleEngine {
    /// <summary>
    /// ����ͼ�������������
    /// </summary>
    class DebugDrawContext
    {
    public:
        DebugDrawGroup* tryGetOrCreateDebugDrawGroup(const std::string& name);//�����µ���
        void clear();//ɾ��������
        void tick(float delta_time) { removeDeadPrimitives(delta_time); }//ÿ֡����Ƿ�������Ҫ�Ƴ�

        std::vector<DebugDrawGroup*> m_debug_draw_groups;//������
    private:
        std::mutex m_mutex;
        void removeDeadPrimitives(float delta_time);
    };
}