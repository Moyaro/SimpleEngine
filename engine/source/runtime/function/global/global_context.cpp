#include "global_context.h"
#include "../render/window_system.h"
#include "../render/render_system.h"
#include "runtime/resource/config_manager/config_manager.h"
#include "runtime/resource/asset_manager/asset_manager.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/function/framework/world/world_manager.h"
#include "core/log/log_system.h"
#include "platform/file_system/file_system.h"
#include "runtime/function/input/input_system.h"
#include "runtime/function/render/render_debug_config.h"

namespace SimpleEngine {
	GlobalContext g_runtime_global_context;

	void GlobalContext::startSystems(const std::string& config_file_path) {
		m_config_manager = std::make_shared<ConfigManager>();
		m_config_manager->init(config_file_path);

		m_file_system = std::make_shared<FileSystem>();

		m_logger_system = std::make_shared<LogSystem>();

		m_asset_manager = std::make_shared<AssetManager>();

		m_world_manager = std::make_shared<WorldManager>();
		m_world_manager->init();

		m_window_system = std::make_shared<WindowSystem>();
		WindowCreateInfo window_create_info;
		m_window_system->init(window_create_info);

		m_input_system = std::make_shared<InputSystem>();
		m_input_system->init();

		m_render_system = std::make_shared<RenderSystem>();
		RenderSystemInitInfo render_init_info;
		render_init_info.window_system = m_window_system;
		m_render_system->init(render_init_info);

		m_debugdraw_manager = std::make_shared<DebugDrawManager>();
		m_debugdraw_manager->init();

		m_render_debug_config = std::make_shared<RenderDebugConfig>();
	}
	void GlobalContext::closeSystems() {
		m_render_debug_config.reset();
		m_debugdraw_manager.reset();

		m_render_system->clear();
		m_render_system.reset();

		m_window_system.reset();

		m_world_manager->clear();
		m_world_manager.reset();

		m_input_system->clear();
		m_input_system.reset();

		m_logger_system.reset();

		m_asset_manager.reset();

		m_file_system.reset();

		m_config_manager.reset();
	}
}