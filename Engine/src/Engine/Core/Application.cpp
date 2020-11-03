#include "Application.hpp"

#include <utility>

namespace Engine {
    Application::Application(const char* p_name, const Version& p_version)
        : Module(p_name)
        , m_name(p_name)
        , m_version(p_version)
    {
    }

    const char* Application::GetName() const
    {
        return m_name;
    }

    const Version& Application::GetVersion() const
    {
        return m_version;
    }
} // namespace Engine