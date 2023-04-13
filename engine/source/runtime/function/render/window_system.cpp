#include "window_system.h"
#include <iostream>

namespace SimpleEngine {
	WindowSystem::~WindowSystem() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	void WindowSystem::init(WindowCreateInfo& create_info) {
		if (!glfwInit()) {
			std::cout << "glfw初始化失败" << std::endl;
			return;
		}

		//获取当前窗口大小
		m_height = create_info.height;
		m_width = create_info.width;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//不创建openGL的上下文

		//创建窗口
		m_window = glfwCreateWindow(m_width, m_height, create_info.title, nullptr, nullptr);
		if (!m_window) {
			std::cout << "窗口创建失败" << std::endl;
			glfwTerminate();
			return;
		}

		//设置输入回调
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetCharCallback(m_window, charCallback);
		glfwSetCharModsCallback(m_window, charModsCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_window, cursorPosCallback);
		glfwSetCursorEnterCallback(m_window, cursorEnterCallback);
		glfwSetScrollCallback(m_window, scrollCallback);
		glfwSetDropCallback(m_window, dropCallback);
		glfwSetWindowSizeCallback(m_window, windowSizeCallback);
		glfwSetWindowCloseCallback(m_window, windowCloseCallback);

		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);//禁用原始鼠标移动
	}

	void WindowSystem::setFocusMode(bool mode)
	{
		m_is_focus_mode = mode;
		glfwSetInputMode(m_window, GLFW_CURSOR, m_is_focus_mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);//焦点模式下鼠标被隐藏、抓取
	}
}