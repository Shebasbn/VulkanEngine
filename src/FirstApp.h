#pragma once
#include "Window.h"

namespace VE
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void Run();
		inline B32 IsRunning() { return m_IsRunning; }

	private:
		Window m_Window{"Vulkan Engine!", WIDTH, HEIGHT};
		B32 m_IsRunning = false;
	};
}

