#include "shader.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    Shader::Shader(const LogicalDevice* logicalDevice, const std::string& path,
                   ShaderType type)
        : m_logicalDevice(logicalDevice)
    {
        spdlog::debug("Create shader: {}", path);

        auto code = FileUtil::readFile(path);

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        Graphics::checkVk(vkCreateShaderModule(m_logicalDevice->getDevice(), &createInfo,
                                               nullptr, &m_shaderModule));

        m_shaderStageInfo = {};
        m_shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_shaderStageInfo.module = m_shaderModule;
        m_shaderStageInfo.pName = "main";

        switch (type) {
            case ShaderType::FragmentShader:
                m_shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                break;
            case ShaderType::VertexShader:
                m_shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
                break;
        }
    }

    Shader::~Shader()
    {
        spdlog::debug("Destroy shader");

        vkDestroyShaderModule(m_logicalDevice->getDevice(), m_shaderModule, nullptr);
    }

    const VkShaderModule& Shader::getShaderModule() const
    {
        return m_shaderModule;
    }

    const VkPipelineShaderStageCreateInfo& Shader::getShaderStageInfo() const
    {
        return m_shaderStageInfo;
    }
} // namespace mineblocks