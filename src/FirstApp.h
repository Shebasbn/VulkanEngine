#pragma once
#include "Window.h"
#include "Pipeline.h"
#include "Device.h"
#include "SwapChain.h"
#include "Model.h"

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
		void LoadModels();
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void FreeCommandBuffers();
		void drawFrame();
		void RecreateSwapChain();
		void RecordCommandBuffer(int imageIndex);

	private:
		Window m_Window{"Vulkan Engine!", WIDTH, HEIGHT};
		Device m_Device{ m_Window };
		std::unique_ptr<SwapChain> m_SwapChain;
		std::unique_ptr<Pipeline> m_Pipeline;
		VkPipelineLayout m_PipelineLayout;
		std::vector<VkCommandBuffer> m_CommandBuffers;
		std::unique_ptr<Model> m_Model;
	};
}

