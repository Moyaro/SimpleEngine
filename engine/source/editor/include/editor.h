#pragma once

#include<memory>
#include "editor_ui.h"
#include "editor_global_context.h"

namespace SimpleEngine {
	
	class Engine;
	
	class Editor {

		friend class EditorUI;

		public:
			Editor();
			void init(Engine* engine_runtime);
			void clear() { g_editor_global_context.clear(); }

			void run();

		protected:
			std::shared_ptr<EditorUI> m_editor_ui;
			Engine* m_engine_runtime{nullptr};
	};

}