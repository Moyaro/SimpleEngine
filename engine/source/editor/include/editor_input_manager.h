#pragma once
#include "runtime/core/math/vector2.h"

#include "runtime/function/render/render_camera.h"

#include <vector>

namespace SimpleEngine
{
    class EngineEditor;

    enum class EditorCommand : unsigned int
    {
        camera_left      = 1 << 0,  // A
        camera_back      = 1 << 1,  // S
        camera_foward    = 1 << 2,  // W
        camera_right     = 1 << 3,  // D
        camera_up        = 1 << 4,  // Q
        camera_down      = 1 << 5,  // E
        translation_mode = 1 << 6,  // T
        rotation_mode    = 1 << 7,  // R
        scale_mode       = 1 << 8,  // C
        exit             = 1 << 9,  // Esc
        delete_object    = 1 << 10, // Delete
    };

    class EditorInputManager
    {
    public:
        void init() { registerInput(); }
        void tick(float delta_time) { processEditorCommand(); }

        void registerInput();//ע��ص��¼�
        void updateCursorOnAxis(Vector2 cursor_uv);//������ģʽ
        void processEditorCommand();//ִ������
        void onKeyInEditorMode(int key, int scancode, int action, int mods);//�༭ģʽ�¼��̵���¼�

        //����ص��¼�
        void onKey(int key, int scancode, int action, int mods);//�����¼�
        void onReset();
        void onCursorPos(double xpos, double ypos);
        void onCursorEnter(int entered);//δ���봰����ʱ���������Ϊ(-1,-1)
        void onScroll(double xoffset, double yoffset);//�����¼���+�Ҽ�=����/���٣�����=��������ӽ�
        void onMouseButtonClicked(int key, int action);//������¼�����pick_pass��ȡmesh_id���Ӷ�ʵ�ֵ����Ӧ����
        void onWindowClosed();//���ڹر��¼����ر�����

        //����Ƿ��ھ��������ڣ�ʵ�ְ�ť����
        bool isCursorInRect(Vector2 pos, Vector2 size) const{ return pos.x <= m_mouse_x && m_mouse_x <= pos.x + size.x && pos.y <= m_mouse_y && m_mouse_y <= pos.y + size.y; }

    public:
        //��ȡ����λ�á���С������ٶ�
        Vector2 getEngineWindowPos() const { return m_engine_window_pos; };
        Vector2 getEngineWindowSize() const { return m_engine_window_size; };
        float   getCameraSpeed() const { return m_camera_speed; };

        //���ô���λ�á���С����������
        void setEngineWindowPos(Vector2 new_window_pos) { m_engine_window_pos = new_window_pos; };
        void setEngineWindowSize(Vector2 new_window_size) { m_engine_window_size = new_window_size; };
        void resetEditorCommand() { m_editor_command = 0; }

    private:
        //����λ�á����
        Vector2 m_engine_window_pos {0.0f, 0.0f};
        Vector2 m_engine_window_size {1280.0f, 768.0f};

        //���λ��
        float   m_mouse_x {0.0f};
        float   m_mouse_y {0.0f};

        float   m_camera_speed {0.05f};//����ƶ��ٶ�

        size_t       m_cursor_on_axis {3};
        unsigned int m_editor_command {0};
    };
}
