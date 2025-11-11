#include "Window.h"

namespace VE
{
	Window::Window(const std::string& title = "Vulkan Engine",
				   U32 width = 1280, U32 height = 720)
		: m_Title(title), m_Width(width), m_Height(height) 
	{
		Init();
	}
	
	void Window::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), 0, 0);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		m_Window = nullptr;
	}
}