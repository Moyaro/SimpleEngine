#pragma once

#include <string>
#include <memory>

namespace SimpleEngine {
	class LogSystem;
	class InputSystem;
	class WindowSystem;
	class RenderSystem;
	class FileSystem;
	class AssetManager;
	class ConfigManager;
	class DebugDrawManager;
	class RenderDebugConfig;
	class WorldManager;

	/// <summary>
	/// 管理所有系统的生命周期
	/// </summary>
	class GlobalContext {
	public:
		void startSystems(const std::string& config_file_path);
		void closeSystems();

	public:
		std::shared_ptr<LogSystem> m_logger_system;
		std::shared_ptr<InputSystem> m_input_system;
		std::shared_ptr<WindowSystem> m_window_system;
		std::shared_ptr<RenderSystem> m_render_system;
		std::shared_ptr<AssetManager> m_asset_manager;
		std::shared_ptr<ConfigManager> m_config_manager;
		std::shared_ptr<FileSystem> m_file_system;
		std::shared_ptr<WorldManager> m_world_manager;
		std::shared_ptr<DebugDrawManager>  m_debugdraw_manager;
		std::shared_ptr<RenderDebugConfig> m_render_debug_config;
	};

	extern GlobalContext g_runtime_global_context;
}