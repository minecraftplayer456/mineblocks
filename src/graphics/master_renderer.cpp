#include "master_renderer.hpp"

#include "core/application.hpp"

namespace mineblocks {
    MasterRenderer::MasterRenderer(Window* window)
        : m_instance()
        , m_physicalDevice(&m_instance)
        , m_surface(&m_instance, &m_physicalDevice, window)
        , m_logicalDevice(&m_instance, &m_physicalDevice, &m_surface)
        , m_swapchain(&m_physicalDevice, &m_logicalDevice, &m_surface,
                      {window->getSize().x, window->getSize().y})
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