#include "engine.h"
#include "runtime/core/meta/reflection/reflection_register.h"
#include "function/global/global_context.h"
#include "function/render/window_system.h"
#include "function/render/render_system.h"
#include "runtime/function/input/input_system.h"
#include "runtime/function/framework/world/world_manager.h"
#include "core/base/macro.h"
#include <string>
#include <iostream>

namespace SimpleEngine {

	bool g_is_editor_mode{false};
	std::unordered_set<std::string> g_editor_tick_component_types;

	//调用全局上下文启动/关闭引擎
	void Engine::startEngine(const std::string& config_file_path) {
		Reflection::TypeMetaRegister::metaRegister();

		g_runtime_global_context.startSystems(config_file_path);
		LOG_INFO("启动引擎");
	}
	void Engine::closeEngine() {
		LOG_INFO("关闭引擎");
		g_runtime_global_context.closeSystems();
		Reflection::TypeMetaRegister::metaUnregister();
	}


	//毛用没有
	void Engine::run() {
		std::shared_ptr<WindowSystem> window_system = g_runtime_global_context.m_window_system;
		while (!window_system->shouldClose())
		{
			const float delta_time = calculateDeltaTime();
			tickOneFrame(delta_time);
		}
	}

	//刷新一帧需要的时间
	float Engine::calculateDeltaTime() {
		float delta_time;
		{
			using namespace std::chrono;
			auto tick_time_point = steady_clock::now();
			duration<float> time_span = duration_cast<duration<float>>(tick_time_point - m_last_tick_time_point);
			delta_time = time_span.count();
			m_last_tick_time_point = tick_time_point;
		}
		return delta_time;
	}

	bool Engine::tickOneFrame(float delta_time) {
		logicalTick(delta_time);
		calculateFPS(delta_time);

		g_runtime_global_context.m_render_system->swapLogicRenderData();

		rendererTick(delta_time);

		g_runtime_global_context.m_window_system->pollEvents();
		g_runtime_global_context.m_window_system->setTitle(std::string("SimpleEngine - 628 - " + std::to_string(getFPS()) + "FPS").c_str());

		//不应该关就返回true
		bool should_window_close = g_runtime_global_context.m_window_system->shouldClose();
		return !should_window_close;
	}

	void Engine::logicalTick(float delta_time) {
		g_runtime_global_context.m_world_manager->tick(delta_time);
		g_runtime_global_context.m_input_system->tick();
	}
	void Engine::rendererTick(float delta_time) {
		g_runtime_global_context.m_render_system->tick(delta_time);
	}

	const float Engine::s_fps_alpha = 1.f / 100.f;
	void Engine::calculateFPS(float delta_time) {
		m_frame_count++;
		if (m_frame_count == 1)
		{
			m_average_duration = delta_time;
		}
		else
		{
			m_average_duration = m_average_duration * (1 - s_fps_alpha) + delta_time * s_fps_alpha;
		}
		m_fps = static_cast<int>(1.f / m_average_duration);
	}
}