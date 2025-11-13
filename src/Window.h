#pragma once

#define GLFW_INCLUDE_VULKAN

#include "Core.h"
#include <GLFW/glfw3.h>
#include <string>

namespace VE
{
	class Window
	{
	public:
		Window(const std::string& title, U32 width, U32 height);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		inline B32 IsRunning() 
		{ 
			m_IsRunning = !glfwWindowShouldClose(m_Window); 
			return m_IsRunning; 
		}

		VkExtent2D GetExtent() { return { m_Width, m_Height }; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		B32 Init();

	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		const U32 m_Width;
		const U32 m_Height;
		B32 m_IsRunning = false;
	};
}
