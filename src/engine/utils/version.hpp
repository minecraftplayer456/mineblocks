#pragma once

#include <string>

namespace engine::utils {
    class Version {
      public:
        Version(int major, int minor, int patch);

        [[nodiscard]] int getMajor() const;
        [[nodiscard]] int getMinor() const;
        [[nodiscard]] int getPatch() const;

        [[nodiscard]] std::string toString() const;
        [[nodiscard]] uint32_t toVulkanVersion() const;

      private:
        int m_major;
        int m_minor;
        int m_patch;
    };
} // namespace engine::utils