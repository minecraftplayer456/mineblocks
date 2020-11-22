#include "Application.hpp"

namespace Engine {
    Application::Application(const char* name, const class Version& version)
        : name(name)
        , version(version)
    {
    }

    auto Application::GetName() const -> const char*
    {
        return name;
    }

    auto Application::GetVersion() const -> const Version&
    {
        return version;
    }
} // namespace Engine