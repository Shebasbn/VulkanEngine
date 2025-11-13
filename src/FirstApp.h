#pragma once
#include "Window.h"
#include "Pipeline.h"
#include "Device.h"
#include "SwapChain.h"

#include <memory>
#include <vector>

namespace VE
{
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void Run();
	private:
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void drawFrame();

	private:
		Window m_Window{"Vulkan Engine!", WIDTH, HEIGHT};
		Device m_Device{ m_Window };
		SwapChain m_SwapChain{ m_Device, m_Window.GetExtent() };
		std::unique_ptr<Pipeline> m_Pipeline;
		VkPipelineLayout m_PipelineLayout;
		std::vector<VkCommandBuffer> m_CommandBuffers;
		/*{
			m_Device, 
			"../Shaders/SimpleShader.vert.spv", 
			"../Shaders/SimpleShader.frag.spv", 
			Pipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT) 
		};*/
	};
}

