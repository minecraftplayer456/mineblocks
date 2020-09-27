#define GLFW_INCLUDE_VULKAN

#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

const uint32_t WIDTH = 900;
const uint32_t HEIGHT = 700;

VkInstance instance;

GLFWwindow* window;

void initWindow(){
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Mineblocks", nullptr, nullptr);
}

void createInstance(){
    VkApplicationInfo  appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Mineblocks";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Mineblocks - Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    spdlog::debug("available extensions:");

    for (const auto& extension : extensions) {
        spdlog::debug(extension.extensionName);
    }
}

void init(){
    createInstance();

    initWindow();
}

void loop(){
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
}

void cleanup(){
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    spdlog::set_level(spdlog::level::trace);

    init();
    loop();
    cleanup();
    return 0;
}
