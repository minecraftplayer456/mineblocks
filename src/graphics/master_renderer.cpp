#include "master_renderer.hpp"

#include "core/application.hpp"

namespace mineblocks {
    MasterRenderer::MasterRenderer()
        : m_instance()
        , m_physicalDevice(&m_instance)
    {
    }

    void MasterRenderer::init()
    {
    }

    void MasterRenderer::render(Application* app)
    {
    }

    void MasterRenderer::cleanup()
    {
    }
} // namespace mineblocks