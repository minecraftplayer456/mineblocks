#include "app.hpp"

#include <utility>

namespace engine {
    App::App(std::string name, const utils::Version& version)
        : m_name(std::move(name))
        , m_version(version)
    {
    }

    std::string App::getName() const
    {
        return m_name;
    }

    utils::Version App::getVersion() const
    {
        return m_version;
    }
} // namespace engine