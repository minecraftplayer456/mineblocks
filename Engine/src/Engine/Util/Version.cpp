#include "Version.hpp"

namespace Engine {
    Version::Version(uint8_t p_major, uint8_t p_minor, uint8_t p_patch)
        : m_major(p_major)
        , m_minor(p_minor)
        , m_patch(p_patch)
    {
    }

    uint8_t Version::GetMajor() const
    {
        return m_major;
    }

    uint8_t Version::GetMinor() const
    {
        return m_minor;
    }

    uint8_t Version::GetPatch() const
    {
        return m_patch;
    }

    std::string Version::ToString() const
    {
        std::stringstream ss;

        ss << static_cast<int>(m_major) << "." << static_cast<int>(m_minor) << "."
           << static_cast<int>(m_patch);

        return ss.str();
    }
} // namespace Engine