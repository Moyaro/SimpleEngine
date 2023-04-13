#include "window_system.h"
#include <iostream>

namespace SimpleEngine {
	WindowSystem::~WindowSystem() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	void WindowSystem::init(WindowCreateInfo& create_info) {
		if (!glfwInit()) {
			std::cout << "glfw��ʼ��ʧ��" << std::endl;
			return;
		}

		//��ȡ��ǰ���ڴ�С
		m_height = create_info.height;
		m_width = create_info.width;

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//������openGL��������

		//��������
		m_window = glfwCreateWindow(m_width, m_height, create_info.title, nullptr, nullptr);
		if (!m_window) {
			std::cout << "���ڴ���ʧ��" << std::endl;
			glfwTerminate();
			return;
		}

		//��������ص�
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

		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);//����ԭʼ����ƶ�
	}

	void WindowSystem::setFocusMode(bool mode)
	{
		m_is_focus_mode = mode;
		glfwSetInputMode(m_window, GLFW_CURSOR, m_is_focus_mode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);//����ģʽ����걻���ء�ץȡ
	}
}