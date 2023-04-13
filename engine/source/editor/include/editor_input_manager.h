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

        void registerInput();//注册回调事件
        void updateCursorOnAxis(Vector2 cursor_uv);//更新轴模式
        void processEditorCommand();//执行命令
        void onKeyInEditorMode(int key, int scancode, int action, int mods);//编辑模式下键盘点击事件

        //输入回调事件
        void onKey(int key, int scancode, int action, int mods);//键盘事件
        void onReset();
        void onCursorPos(double xpos, double ypos);
        void onCursorEnter(int entered);//未进入窗口内时，鼠标坐标为(-1,-1)
        void onScroll(double xoffset, double yoffset);//滚轮事件：+右键=加速/减速，不加=缩放相机视角
        void onMouseButtonClicked(int key, int action);//鼠标点击事件：用pick_pass获取mesh_id，从而实现点击对应物体
        void onWindowClosed();//窗口关闭事件：关闭引擎

        //鼠标是否在矩形区域内，实现按钮功能
        bool isCursorInRect(Vector2 pos, Vector2 size) const{ return pos.x <= m_mouse_x && m_mouse_x <= pos.x + size.x && pos.y <= m_mouse_y && m_mouse_y <= pos.y + size.y; }

    public:
        //获取窗口位置、大小，相机速度
        Vector2 getEngineWindowPos() const { return m_engine_window_pos; };
        Vector2 getEngineWindowSize() const { return m_engine_window_size; };
        float   getCameraSpeed() const { return m_camera_speed; };

        //设置窗口位置、大小，重置命令
        void setEngineWindowPos(Vector2 new_window_pos) { m_engine_window_pos = new_window_pos; };
        void setEngineWindowSize(Vector2 new_window_size) { m_engine_window_size = new_window_size; };
        void resetEditorCommand() { m_editor_command = 0; }

    private:
        //窗口位置、宽高
        Vector2 m_engine_window_pos {0.0f, 0.0f};
        Vector2 m_engine_window_size {1280.0f, 768.0f};

        //鼠标位置
        float   m_mouse_x {0.0f};
        float   m_mouse_y {0.0f};

        float   m_camera_speed {0.05f};//相机移动速度

        size_t       m_cursor_on_axis {3};
        unsigned int m_editor_command {0};
    };
}
