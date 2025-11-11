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


	private:
		void Init();

	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		const U32 m_Width;
		const U32 m_Height;
	};
}
