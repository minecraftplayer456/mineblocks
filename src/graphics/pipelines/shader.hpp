#pragma once

#include <string>

#include "devices/logical_device.hpp"
#include "utils/file_util.hpp"

namespace mineblocks {
    enum class ShaderType { FragmentShader, VertexShader };

    class Shader {
      public:
        Shader(const LogicalDevice* logicalDevice, const std::string& path,
               ShaderType type);
        ~Shader();

        [[nodiscard]] const VkShaderModule& getShaderModule() const;
        [[nodiscard]] const VkPipelineShaderStageCreateInfo& getShaderStageInfo() const;

      private:
        const LogicalDevice* m_logicalDevice;

        VkShaderModule m_shaderModule;
        VkPipelineShaderStageCreateInfo m_shaderStageInfo;
    };
} // namespace mineblocks
