#include "../include/editor.h"
#include "../../runtime/engine.h"
#include "../include/editor_global_context.h"
#include "runtime/function/global/global_context.h"
#include <cassert>
#include "editor/include/editor_input_manager.h"
#include "editor/include/editor_scene_manager.h"

namespace SimpleEngine {

	void registerEdtorTickComponent(std::string component_type_name){
		g_editor_tick_component_types.insert(component_type_name);
	}

	//注册需要tick的组件
	Editor::Editor() {
		registerEdtorTickComponent("TransformComponent");
		registerEdtorTickComponent("MeshComponent");
	}

	 void Editor::init(Engine* engine_runtime) {
		 assert(engine_runtime);

		 g_is_editor_mode = true;
		 m_engine_runtime = engine_runtime;
		 
		 //建立编辑器全局信息
		 std::shared_ptr<Engine> engine(engine_runtime);
		 EditorGlobalContextInitInfo init_info = { g_runtime_global_context.m_window_system,g_runtime_global_context.m_render_system,engine};
		 g_editor_global_context.init(init_info);
		 g_editor_global_context.m_scene_manager->setEditorCamera(g_runtime_global_context.m_render_system->getRenderCamera());
		 g_editor_global_context.m_scene_manager->uploadAxisResource();

		 m_editor_ui = std::make_shared<EditorUI>();
		 WindowUIInitInfo ui_init_info = { g_runtime_global_context.m_window_system,g_runtime_global_context.m_render_system };
		 m_editor_ui->init(ui_init_info);

	}

	 void Editor::run() {
		float delta_time = 0;
		do {
			delta_time = m_engine_runtime->calculateDeltaTime();
			g_editor_global_context.m_scene_manager->tick(delta_time);
			g_editor_global_context.m_input_manager->tick(delta_time);
		} while (m_engine_runtime->tickOneFrame(delta_time));
	}
}