#pragma once
#include <memory>

namespace SimpleEngine
{
    class WindowSystem;
    class RenderSystem;
    class EditorSceneManager;
    class EditorInputManager;
    class Engine;

    struct EditorGlobalContextInitInfo
    {
        std::shared_ptr<WindowSystem> window_system;
        std::shared_ptr<RenderSystem> render_system;
        std::shared_ptr<Engine> engine_runtime;
    };

    /// <summary>
    /// 编辑器上下文：初始化编辑器的场景、输入管理器
    /// </summary>
    class EditorGlobalContext
    {
    public:
        std::shared_ptr<EditorSceneManager> m_scene_manager;
        std::shared_ptr<EditorInputManager> m_input_manager;
        std::shared_ptr<RenderSystem> m_render_system;
        std::shared_ptr<WindowSystem> m_window_system;
        std::shared_ptr<Engine> m_engine_runtime;

    public:
        void init(const EditorGlobalContextInitInfo& init_info);
        void clear();
    };

    extern EditorGlobalContext g_editor_global_context;
}