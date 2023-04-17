#pragma once

#include "runtime/core/math/math.h"

namespace SimpleEngine
{
    enum class GameCommand : unsigned int
    {
        forward  = 1 << 0,                 // W
        backward = 1 << 1,                 // S
        left     = 1 << 2,                 // A
        right    = 1 << 3,                 // D
        jump     = 1 << 4,                 // SPACE
        squat    = 1 << 5,                 // 
        sprint   = 1 << 6,                 // LEFT SHIFT
        fire     = 1 << 7,                 // 
        free_carema = 1 << 8,              // F
        invalid  = (unsigned int)(1 << 31) // lost focus
    };

    extern unsigned int k_complement_control_command;//��ɵ�����

    class InputSystem
    {

    public:
        void onKey(int key, int scancode, int action, int mods);//��Ϸģʽ�µļ�������
        void onCursorPos(double current_cursor_x, double current_cursor_y);

        void init();//��ȡ����ϵͳ��ע��ص�����
        void tick();
        void clear();//�������ƶ���

        //����ƶ���
        int m_cursor_delta_x {0};
        int m_cursor_delta_y {0};

        //��������Ƕ�
        Radian m_cursor_delta_yaw {0};
        Radian m_cursor_delta_pitch {0};

        //��ȡ��������
        void         resetGameCommand() { m_game_command = 0; }
        unsigned int getGameCommand() const { return m_game_command; }

    private:
        void onKeyInGameMode(int key, int scancode, int action, int mods);

        void calculateCursorDeltaAngles();

        unsigned int m_game_command {0};

        int m_last_cursor_x {0};
        int m_last_cursor_y {0};
    };
}
