#pragma once

#include "editor/include/axis.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/framework/object/object.h"
#include "runtime/function/render/render_object.h"

#include <memory>

namespace SimpleEngine
{
    class EngineEditor;
    class RenderCamera;
    class RenderEntity;

    enum class EditorAxisMode : int
    {
        TranslateMode = 0,
        RotateMode = 1,
        ScaleMode = 2,
        Default = 3
    };

    class EditorSceneManager
    {
    public:
        void init(){}
        void tick(float delta_time);

    public:
        size_t   updateCursorOnAxis(
            Vector2 cursor_uv,
            Vector2 game_engine_window_size);
        void drawSelectedEntityAxis();//绘制对应模式的轴
        std::weak_ptr<GObject> getSelectedGObject() const;//用id获取选中的物体
        RenderEntity* getAxisMeshByType(EditorAxisMode axis_mode);//获取对应类型的轴网格

        void onGObjectSelected(GObjectID selected_gobject_id);//物体被选中的事件
        void onDeleteSelectedGObject();//删除选中物体的事件

        //移动物体
        void moveEntity(float     new_mouse_pos_x,
            float     new_mouse_pos_y,
            float     last_mouse_pos_x,
            float     last_mouse_pos_y,
            Vector2   engine_window_pos,
            Vector2   engine_window_size,
            size_t    cursor_on_axis,
            Matrix4x4 model_matrix);

        void setEditorCamera(std::shared_ptr<RenderCamera> camera) { m_camera = camera; }
        void uploadAxisResource();
        size_t getGuidOfPickedMesh(const Vector2& picked_uv) const{ return g_editor_global_context.m_render_system->getGuidOfPickedMesh(picked_uv); }

    public:
        std::shared_ptr<RenderCamera> getEditorCamera() { return m_camera; };

        GObjectID getSelectedObjectID() { return m_selected_gobject_id; };
        Matrix4x4 getSelectedObjectMatrix() { return m_selected_object_matrix; }
        EditorAxisMode getEditorAxisMode() { return m_axis_mode; }

        void setSelectedObjectID(GObjectID selected_gobject_id) { m_selected_gobject_id = selected_gobject_id; };
        void setSelectedObjectMatrix(Matrix4x4 new_object_matrix) { m_selected_object_matrix = new_object_matrix; }
        void setEditorAxisMode(EditorAxisMode new_axis_mode) { m_axis_mode = new_axis_mode; }
    private:
        //轴
        EditorTranslationAxis m_translation_axis;
        EditorRotationAxis    m_rotation_axis;
        EditorScaleAxis       m_scale_aixs;

        //选中的物体的id、transform矩阵
        GObjectID m_selected_gobject_id{ k_invalid_gobject_id };
        Matrix4x4 m_selected_object_matrix{ Matrix4x4::IDENTITY };

        EditorAxisMode m_axis_mode{ EditorAxisMode::TranslateMode };//当前轴模式
        std::shared_ptr<RenderCamera> m_camera;//相机

        size_t m_selected_axis{ 3 };//选择的轴

        bool   m_is_show_axis = true;
    };
}