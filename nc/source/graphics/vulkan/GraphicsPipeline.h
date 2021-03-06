#pragma once

#include "vulkan/vulkan.hpp"

namespace nc::graphics::vulkan
{
    class Device; class RenderPass;

    class GraphicsPipeline
    {
        public:
            GraphicsPipeline(const vulkan::Device& device, const vulkan::RenderPass& renderPass); // &todo: Change from passing in a single render pass
            const vk::Pipeline& GetPipeline() const;

        private:
            vk::UniquePipelineLayout m_pipelineLayout;
            vk::UniquePipeline m_pipeline;
            vk::ShaderModule CreateShaderModule(const std::vector<uint32_t>& code, const vulkan::Device& device);
    };
}