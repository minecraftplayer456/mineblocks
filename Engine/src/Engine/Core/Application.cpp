#include "Application.hpp"

#include <utility>

namespace Engine {
    Application::Application(std::string p_name, const Version& p_version)
        : m_name(std::move(p_name))
        , m_version(p_version)
    {
    }

    const std::string& Application::GetName() const
    {
        return m_name;
    }

    const Version& Application::GetVersion() const
    {
        return m_version;
    }
} // namespace Engine