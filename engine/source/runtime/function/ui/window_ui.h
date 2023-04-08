#pragma once

#include <memory>

namespace SimpleEngine {

	class WindowSystem;
	class RenderSystem;

	/// <summary>
	/// 窗口界面初始化信息
	/// </summary>
	struct WindowUIInitInfo {
		std::shared_ptr<WindowSystem> window_system;
		std::shared_ptr<RenderSystem> render_system;
	};

	//用窗口和渲染系统初始化
	class WindowUI
	{
	public:
		virtual void init(WindowUIInitInfo init_info) = 0;
		virtual void preRender() = 0;
	};
}