#include "editor/include/editor_global_context.h"

#include "editor/include/editor_input_manager.h"
#include "editor/include/editor_scene_manager.h"

#include "runtime/function/render/render_system.h"
#include "runtime/function/render/window_system.h"

namespace SimpleEngine
{
    EditorGlobalContext g_editor_global_context;

    void EditorGlobalContext::init(const EditorGlobalContextInitInfo& init_info)
    {
        g_editor_global_context.m_window_system = init_info.window_system;
        g_editor_global_context.m_render_system = init_info.render_system;
        g_editor_global_context.m_engine_runtime = init_info.engine_runtime;

        m_scene_manager = std::make_shared<EditorSceneManager>();
        m_input_manager = std::make_shared<EditorInputManager>();
        m_scene_manager->init();
        m_input_manager->init();
    }

    void EditorGlobalContext::clear()
    {
        m_scene_manager.reset();
        m_input_manager.reset();
    }
}