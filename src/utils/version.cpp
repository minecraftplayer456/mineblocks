#include "version.hpp"

#include <vulkan/vulkan.h>

namespace engine::utils {
    Version::Version(int major, int minor, int patch)
        : m_major(major)
        , m_minor(minor)
        , m_patch(patch)
    {
    }

    int Version::getMajor() const
    {
        return m_major;
    }

    int Version::getMinor() const
    {
        return m_minor;
    }

    int Version::getPatch() const
    {
        return m_patch;
    }

    int Version::asVkVersion() const
    {
        return VK_MAKE_VERSION(m_major, m_minor, m_patch);
    }
} // namespace engine::utils