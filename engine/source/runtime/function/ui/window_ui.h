#pragma once

#include <memory>

namespace SimpleEngine {

	class WindowSystem;
	class RenderSystem;

	/// <summary>
	/// ���ڽ����ʼ����Ϣ
	/// </summary>
	struct WindowUIInitInfo {
		std::shared_ptr<WindowSystem> window_system;
		std::shared_ptr<RenderSystem> render_system;
	};

	//�ô��ں���Ⱦϵͳ��ʼ��
	class WindowUI
	{
	public:
		virtual void init(WindowUIInitInfo init_info) = 0;
		virtual void preRender() = 0;
	};
}