#include "editor/include/editor_input_manager.h"
#include "runtime/function/input/input_system.h"
#include "editor/include/editor.h"
#include "editor/include/editor_scene_manager.h"
#include "runtime/function/framework/level/level.h"
#include "runtime/function/framework/world/world_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/render/window_system.h"
#include "runtime/engine.h"
#include "editor/include/editor_global_context.h"

namespace SimpleEngine{ 
    
    void EditorInputManager::onWindowClosed() { g_editor_global_context.m_engine_runtime->closeEngine(); }

    void EditorInputManager::registerInput()
    {
        g_editor_global_context.m_window_system->registerOnResetFunc(std::bind(&EditorInputManager::onReset, this));
        g_editor_global_context.m_window_system->registerOnCursorPosFunc(std::bind(&EditorInputManager::onCursorPos, this, std::placeholders::_1, std::placeholders::_2));
        g_editor_global_context.m_window_system->registerOnCursorEnterFunc(std::bind(&EditorInputManager::onCursorEnter, this, std::placeholders::_1));
        g_editor_global_context.m_window_system->registerOnScrollFunc(std::bind(&EditorInputManager::onScroll, this, std::placeholders::_1, std::placeholders::_2));
        g_editor_global_context.m_window_system->registerOnMouseButtonFunc(std::bind(&EditorInputManager::onMouseButtonClicked, this, std::placeholders::_1, std::placeholders::_2));
        g_editor_global_context.m_window_system->registerOnWindowCloseFunc(std::bind(&EditorInputManager::onWindowClosed, this));
        g_editor_global_context.m_window_system->registerOnKeyFunc(std::bind(&EditorInputManager::onKey,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    }

    void EditorInputManager::updateCursorOnAxis(Vector2 cursor_uv)
    {
        if (g_editor_global_context.m_scene_manager->getEditorCamera())
        {
            Vector2 window_size(m_engine_window_size.x, m_engine_window_size.y);
            m_cursor_on_axis = g_editor_global_context.m_scene_manager->updateCursorOnAxis(cursor_uv, window_size);
        }
    }

    void EditorInputManager::processEditorCommand()
    {
        float           camera_speed  = m_camera_speed;
        std::shared_ptr editor_camera = g_editor_global_context.m_scene_manager->getEditorCamera();
        Quaternion      camera_rotate = editor_camera->rotation().inverse();//�����ת����
        Vector3         camera_relative_pos(0, 0, 0);//������λ��

        //��鵱ǰ��Ҫִ�е�����
        if ((unsigned int)EditorCommand::camera_foward & m_editor_command)
        {
            camera_relative_pos += camera_rotate * Vector3 {0, camera_speed, 0};
        }
        if ((unsigned int)EditorCommand::camera_back & m_editor_command)
        {
            camera_relative_pos += camera_rotate * Vector3 {0, -camera_speed, 0};
        }
        if ((unsigned int)EditorCommand::camera_left & m_editor_command)
        {
            camera_relative_pos += camera_rotate * Vector3 {-camera_speed, 0, 0};
        }
        if ((unsigned int)EditorCommand::camera_right & m_editor_command)
        {
            camera_relative_pos += camera_rotate * Vector3 {camera_speed, 0, 0};
        }
        if ((unsigned int)EditorCommand::camera_up & m_editor_command)
        {
            camera_relative_pos += Vector3 {0, 0, camera_speed};
        }
        if ((unsigned int)EditorCommand::camera_down & m_editor_command)
        {
            camera_relative_pos += Vector3 {0, 0, -camera_speed};
        }
        if ((unsigned int)EditorCommand::delete_object & m_editor_command)
        {
            g_editor_global_context.m_scene_manager->onDeleteSelectedGObject();
        }

        editor_camera->move(camera_relative_pos);
    }

    void EditorInputManager::onKeyInEditorMode(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            //��ť���£�Ϊ��Ӧ������������
            switch (key)
            {
                case GLFW_KEY_A:
                    m_editor_command |= (unsigned int)EditorCommand::camera_left;
                    break;
                case GLFW_KEY_S:
                    m_editor_command |= (unsigned int)EditorCommand::camera_back;
                    break;
                case GLFW_KEY_W:
                    m_editor_command |= (unsigned int)EditorCommand::camera_foward;
                    break;
                case GLFW_KEY_D:
                    m_editor_command |= (unsigned int)EditorCommand::camera_right;
                    break;
                case GLFW_KEY_Q:
                    m_editor_command |= (unsigned int)EditorCommand::camera_up;
                    break;
                case GLFW_KEY_E:
                    m_editor_command |= (unsigned int)EditorCommand::camera_down;
                    break;
                case GLFW_KEY_T:
                    m_editor_command |= (unsigned int)EditorCommand::translation_mode;
                    break;
                case GLFW_KEY_R:
                    m_editor_command |= (unsigned int)EditorCommand::rotation_mode;
                    break;
                case GLFW_KEY_C:
                    m_editor_command |= (unsigned int)EditorCommand::scale_mode;
                    break;
                case GLFW_KEY_DELETE:
                    m_editor_command |= (unsigned int)EditorCommand::delete_object;
                    break;
                default:
                    break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            //��ť�ͷţ�Ϊ��Ӧ�����ͷ�����
            switch (key)
            {
                case GLFW_KEY_ESCAPE:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::exit);
                    break;
                case GLFW_KEY_A:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_left);
                    break;
                case GLFW_KEY_S:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_back);
                    break;
                case GLFW_KEY_W:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_foward);
                    break;
                case GLFW_KEY_D:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_right);
                    break;
                case GLFW_KEY_Q:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_up);
                    break;
                case GLFW_KEY_E:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::camera_down);
                    break;
                case GLFW_KEY_T:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::translation_mode);
                    break;
                case GLFW_KEY_R:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::rotation_mode);
                    break;
                case GLFW_KEY_C:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::scale_mode);
                    break;
                case GLFW_KEY_DELETE:
                    m_editor_command &= (k_complement_control_command ^ (unsigned int)EditorCommand::delete_object);
                    break;
                default:
                    break;
            }
        }
    }

    void EditorInputManager::onKey(int key, int scancode, int action, int mods)
    {
        if (g_is_editor_mode)
        {
            onKeyInEditorMode(key, scancode, action, mods);
        }
    }

    void EditorInputManager::onReset()
    {
        // to do
    }

    void EditorInputManager::onCursorPos(double xpos, double ypos)
    {
        if (!g_is_editor_mode)
            return;

        float angularVelocity = 180.0f / Math::max(m_engine_window_size.x, m_engine_window_size.y); //���ٶȣ���������ڲ�ͬ�ֱ��ʺ���Ļ�ߴ��µ���ת�ٶ�һ��
        if (m_mouse_x >= 0.0f && m_mouse_y >= 0.0f)//���֮ǰ����ڴ�����
        {
            if (g_editor_global_context.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))//�������Ҽ��ƶ���������꣬�����ת
            {
                glfwSetInputMode(g_editor_global_context.m_window_system->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                g_editor_global_context.m_scene_manager->getEditorCamera()->rotate(Vector2(ypos - m_mouse_y, xpos - m_mouse_x) * angularVelocity);
            }
            else if (g_editor_global_context.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))//����������ƶ����ƶ����壬�������ģʽΪnormal
            {
                g_editor_global_context.m_scene_manager->moveEntity(
                    xpos,
                    ypos,
                    m_mouse_x,
                    m_mouse_y,
                    m_engine_window_pos,
                    m_engine_window_size,
                    m_cursor_on_axis,
                    g_editor_global_context.m_scene_manager->getSelectedObjectMatrix());
                glfwSetInputMode(g_editor_global_context.m_window_system->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else//δ���κΰ��������ù��ģʽΪnormal����ǰ����ڴ�����ʱ���ù���uv���꣬�������λ��
            {
                glfwSetInputMode(g_editor_global_context.m_window_system->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

                if (isCursorInRect(m_engine_window_pos, m_engine_window_size))
                {
                    Vector2 cursor_uv = Vector2((m_mouse_x - m_engine_window_pos.x) / m_engine_window_size.x,
                                                (m_mouse_y - m_engine_window_pos.y) / m_engine_window_size.y);
                    updateCursorOnAxis(cursor_uv);
                }
            }
        }
        //���������λ��
        m_mouse_x = xpos;
        m_mouse_y = ypos;
    }

    void EditorInputManager::onCursorEnter(int entered)
    {
        if (!entered) //ʧȥ����
        {
            m_mouse_x = m_mouse_y = -1.0f;
        }
    }

    void EditorInputManager::onScroll(double xoffset, double yoffset)
    {
        if (!g_is_editor_mode)
        {
            return;
        }

        //����ڴ����ڣ�
        if (isCursorInRect(m_engine_window_pos, m_engine_window_size))
        {
            if (g_editor_global_context.m_window_system->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))//�������Ҽ�
            {
                if (yoffset > 0)//�������ƣ�����
                {
                    m_camera_speed *= 1.2f;
                }
                else//�������ƣ�����
                {
                    m_camera_speed *= 0.8f;
                }
            }
            else//û���Ҽ�����������ӽ�
            {
                g_editor_global_context.m_scene_manager->getEditorCamera()->zoom((float)yoffset * 2.0f);
            }
        }
    }

    void EditorInputManager::onMouseButtonClicked(int key, int action)
    {
        if (!g_is_editor_mode)
            return;
        if (m_cursor_on_axis != 3)
            return;

        //��ȡ��ǰlevel
        std::shared_ptr<Level> current_active_level = g_runtime_global_context.m_world_manager->getCurrentActiveLevel().lock();
        if (current_active_level == nullptr)
            return;

        //����ڴ�����
        if (isCursorInRect(m_engine_window_pos, m_engine_window_size))
        {
            if (key == GLFW_MOUSE_BUTTON_LEFT)//������
            {
                //ͨ��picked_uv��ȡ����id
                Vector2 picked_uv((m_mouse_x - m_engine_window_pos.x) / m_engine_window_size.x,
                                  (m_mouse_y - m_engine_window_pos.y) / m_engine_window_size.y);
                size_t  select_mesh_id = g_editor_global_context.m_scene_manager->getGuidOfPickedMesh(picked_uv);

                size_t gobject_id = g_editor_global_context.m_render_system->getGObjectIDByMeshID(select_mesh_id);//��ȡguid
                g_editor_global_context.m_scene_manager->onGObjectSelected(gobject_id);//�����������¼�
            }
        }
    }
}