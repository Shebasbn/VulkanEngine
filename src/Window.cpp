#include "Window.h"
#include <iostream>

namespace VE
{
	Window::Window(const std::string& title = "Vulkan Engine",
				   U32 width = 1280, U32 height = 720)
		: m_Title(title), m_Width(width), m_Height(height) 
	{
		m_IsRunning = Init();
	}
	
	void Window::FrameBufferResizedCallback(GLFWwindow* glfwWindow, int width, int height)
	{
		auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
		window->m_FrameBufferResized = true;
		window->m_Width = width;
		window->m_Height = height;
	}

	B32 Window::Init()
	{
		if (glfwInit() == GLFW_FALSE) return false;
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), 0, 0);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, FrameBufferResizedCallback);

		return (B32)m_Window;
	}

	void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS)
		{
			std::cout << "Failed to create a window surface!" << std::endl;
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		m_Window = nullptr;
	}
}