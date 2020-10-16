#include "instance.hpp"

#include <stdexcept>

#include "app.hpp"
#include "graphics/graphics.hpp"

namespace engine::devices::graphics {
    void Instance::create(const App& app)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = app.getName().c_str();
        appInfo.applicationVersion = app.getVersion().asVkVersion();
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = engineVersion.asVkVersion();
        appInfo.apiVersion = vkApiVersion;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        engine::graphics::assertVkResult(
            vkCreateInstance(&createInfo, nullptr, &m_instance));
    }

    void Instance::destroy()
    {
        vkDestroyInstance(m_instance, nullptr);
    }

    VkInstance Instance::getInstance() const
    {
        return m_instance;
    }
} // namespace engine::devices::graphics