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

		VkExtent2D GetExtent() const { return { m_Width, m_Height }; }
		B32 WasWindowResized() const { return m_FrameBufferResized; }
		void ResetWindowResizedFlag() { m_FrameBufferResized = false; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		static void FrameBufferResizedCallback(GLFWwindow* window, int width, int height);
		B32 Init();

	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		U32 m_Width;
		U32 m_Height;
		B32 m_FrameBufferResized = false;
		B32 m_IsRunning = false;
	};
}
