#include "debug_draw_primitive.h"

namespace SimpleEngine {
	bool DebugDrawPrimitive::isTimeOut(float delta_time) {//���Ƿ�ֹͣ��Ⱦ
		if (m_time_type == _debugDrawTimeType_infinity) return false;
		else if (m_time_type == _debugDrawTimeType_one_frame) {//ֻ��Ⱦһ�ξͽ�����������
			if (!m_rendered) {
				m_rendered = true;
				return false;
			}
			else return true;
		}
		else {
			m_life_time -= delta_time;
			return m_life_time < 0.0f;
		}
	}

	//������Ⱦ����ʱ��
	void DebugDrawPrimitive::setTime(float in_life_time) {
		if (in_life_time == k_debug_draw_infinity_life_time)
		{
			m_time_type = _debugDrawTimeType_infinity;
			m_life_time = 0.0f;
		}
		else if (in_life_time == k_debug_draw_one_frame)
		{
			m_time_type = _debugDrawTimeType_one_frame;
			m_life_time = 0.03f;
		}
		else
		{
			m_time_type = _debugDrawTimeType_common;
			m_life_time = in_life_time;
		}
	}
}