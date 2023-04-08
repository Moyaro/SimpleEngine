#pragma once

#include <string>
#include <unordered_set>
#include <chrono>

namespace SimpleEngine {

	extern bool g_is_editor_mode;
	extern std::unordered_set<std::string> g_editor_tick_component_types;

	class Engine {
		friend class Editor;

		static const float s_fps_alpha;//fps计算用参数

		public:
			void startEngine(const std::string& config_file_path);
			void closeEngine();

			void run();
			bool tickOneFrame(float delta_time);
			int getFPS() const { return m_fps; }

		protected:
			float calculateDeltaTime();//每帧只被调用一次
			void logicalTick(float delta_time);
			void rendererTick(float delta_time);
			void calculateFPS(float delta_time);
			
		protected:
			std::chrono::steady_clock::time_point m_last_tick_time_point{std::chrono::steady_clock::now()};

			//计算帧率用
			float m_average_duration{ 0.f };
			int m_frame_count{ 0 };
			int m_fps{ 0 };
	};
}