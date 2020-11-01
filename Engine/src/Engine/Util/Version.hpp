#pragma once

namespace Engine {
    class Version {
      public:
        Version(uint8_t p_major, uint8_t p_minor, uint8_t p_patch);

        [[nodiscard]] uint8_t GetMajor() const;
        [[nodiscard]] uint8_t GetMinor() const;
        [[nodiscard]] uint8_t GetPatch() const;

        [[nodiscard]] std::string ToString() const;

      private:
        uint8_t m_major;
        uint8_t m_minor;
        uint8_t m_patch;
    };
} // namespace Engine