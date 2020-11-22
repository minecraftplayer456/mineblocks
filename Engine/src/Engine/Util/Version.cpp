#include "Version.hpp"

namespace Engine {
    Version::Version(uint8_t major, uint8_t minor, uint8_t patch)
        : major(major)
        , minor(minor)
        , patch(patch)
    {
    }

    auto Version::GetMajor() const -> uint8_t
    {
        return major;
    }

    auto Version::GetMinor() const -> uint8_t
    {
        return minor;
    }

    auto Version::GetPatch() const -> uint8_t
    {
        return patch;
    }

    auto Version::ToString() const -> std::string
    {
        std::stringstream ss;

        ss << static_cast<int>(major) << "." << static_cast<int>(minor) << "."
           << static_cast<int>(patch);

        return ss.str();
    }
} // namespace Engine