#include "FirstApp.h"
#include <print>
#include <array>

namespace VE
{
	FirstApp::FirstApp()
	{
		CreatePipelineLayout();
		CreatePipeline();
		CreateCommandBuffers();
	}
	FirstApp::~FirstApp()
	{
		vkDestroyPipelineLayout(m_Device.device(), m_PipelineLayout, nullptr);
	}
	void FirstApp::Run()
	{
		while (m_Window.IsRunning())
		{
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(m_Device.device());
	}
	void FirstApp::CreatePipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(m_Device.device(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
		{
			std::println("Failed to create a pipeline layout!");
			return;
		}

	}
	void FirstApp::CreatePipeline()
	{
		auto pipelineConfig = Pipeline::DefaultPipelineConfigInfo(m_SwapChain.width(), m_SwapChain.height());
		pipelineConfig.renderPass = m_SwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = m_PipelineLayout;
		m_Pipeline = std::make_unique<Pipeline>(
			m_Device, 
			"../Shaders/SimpleShader.vert.spv", 
			"../Shaders/SimpleShader.frag.spv", 
			pipelineConfig);
	}
	void FirstApp::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(m_SwapChain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_Device.getCommandPool();
		allocInfo.commandBufferCount = static_cast<U32>(m_CommandBuffers.size());

		if (vkAllocateCommandBuffers(m_Device.device(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		{
			std::println("Failed to create command buffers!");
			return;
		}

		for (int i = 0; i < m_CommandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(m_CommandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				std::println("Command Buffer Failed to Begin Recording!");
				return;
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = m_SwapChain.getRenderPass();
			renderPassInfo.framebuffer = m_SwapChain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = m_SwapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 0.1f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<U32>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(m_CommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			m_Pipeline->bind(m_CommandBuffers[i]);
			vkCmdDraw(m_CommandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(m_CommandBuffers[i]);
			if (vkEndCommandBuffer(m_CommandBuffers[i]) != VK_SUCCESS)
			{
				std::println("Failed to record command buffer!");
				return;
			}
		}
	}
	void FirstApp::drawFrame()
	{
		U32 imageIndex;
		auto result = m_SwapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			std::println("Failed to aquire next swapchain image!");
			return;
		}

		result = m_SwapChain.submitCommandBuffers(&m_CommandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
		{
			std::println("Failed to present swap chain image!");
			return;
		}
	}
}