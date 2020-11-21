#include "Application.hpp"

namespace Engine {
    Application::Application(const char* name, const class Version& version)
        : Name(name)
        , Version(version)
    {
    }

    const char* Application::GetName() const
    {
        return Name;
    }

    const Version& Application::GetVersion() const
    {
        return Version;
    }
} // namespace Engine