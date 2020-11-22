#pragma once

namespace Engine {
    class Version {
      public:
        Version(uint8_t major, uint8_t minor, uint8_t patch);

        [[nodiscard]] auto GetMajor() const -> uint8_t;
        [[nodiscard]] auto GetMinor() const -> uint8_t;
        [[nodiscard]] auto GetPatch() const -> uint8_t;

        [[nodiscard]] auto ToString() const -> std::string;

      private:
        uint8_t major;
        uint8_t minor;
        uint8_t patch;
    };
} // namespace Engine