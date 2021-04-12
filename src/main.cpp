#include "window.hpp"
#include "validation.hpp"
#include "device_list.hpp"
#include <utility>
#include <cstdio>
#include <cassert>
#include <memory>

struct VulkanInstance
{
    VulkanInstance(VkInstanceCreateInfo& create_info)
    {
        if(vkd::valid::detail::validation_layers_enabled)
        {
            assert(vkd::valid::confirm_layer_support());
        }
        this->should_destroy = vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS;
    }
    VulkanInstance(const VulkanInstance& copy) = delete;
    VulkanInstance(VulkanInstance&& move): instance(move.instance), should_destroy(false)
    {
        std::swap(this->should_destroy, move.should_destroy);
    }
    ~VulkanInstance()
    {
        if(this->should_destroy)
        {
            vkDestroyInstance(this->instance, nullptr);
        }
    }

    VkInstance get() const
    {
        return this->instance;
    }
private:
    VkInstance instance;
    bool should_destroy;
};

struct VulkanContext
{
    VkApplicationInfo app_info = {};
    VkInstanceCreateInfo create_info = {};
    std::unique_ptr<VulkanInstance> instance = nullptr;
};

void go();
VulkanContext init_vulkan();

int main()
{
    glfwInit();
    go();
    glfwTerminate();
    return 0;
}

void go()
{
    // GLFW defaults to OGL. No thanks
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // No resize support
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    vkd::Window wnd{800, 600, "Vulkan Demo"};
    {
        VulkanContext ctx = init_vulkan();
        while(!wnd.should_close())
        {
            wnd.update();
        }
    }
}

VulkanContext init_vulkan()
{
    VulkanContext ctx;
    // Application info.
    ctx.app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    ctx.app_info.pApplicationName = "Vulkan Demo";
    ctx.app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    ctx.app_info.pEngineName = "No Engine";
    ctx.app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    ctx.app_info.apiVersion = VK_API_VERSION_1_0;

    // Extensions info.
    ctx.create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ctx.create_info.pApplicationInfo = &ctx.app_info;

    std::uint32_t num_extensions = 0;
    const char** extensions;
    // glfwGetRequiredInstanceExtensions is used to get all the extensions we need for VK to interface with the "window system".
    extensions = glfwGetRequiredInstanceExtensions(&num_extensions);

    // Tell Vulkan the extensions we're using.
    ctx.create_info.enabledExtensionCount = num_extensions;
    ctx.create_info.ppEnabledExtensionNames = extensions;
    // Validation Layers
    if(vkd::valid::detail::validation_layers_enabled)
    {
        ctx.create_info.enabledLayerCount = static_cast<std::uint32_t>(vkd::valid::detail::validation_layers.size());
        ctx.create_info.ppEnabledLayerNames = vkd::valid::detail::validation_layers.data();
    }
    else
    {
        ctx.create_info.enabledLayerCount = 0;
    }
    ctx.instance = std::make_unique<VulkanInstance>(ctx.create_info);
    VkInstance vki = ctx.instance->get();
    // Let's choose a device.
    vkd::DeviceList devs = vkd::enumerate_devices(vki);
    std::printf("All Devices (%d):\n", static_cast<int>(devs.size()));
    for(const auto& dev : devs)
    {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(dev, &props);
        std::printf("\t- \"%s\"\n", props.deviceName);
    }
    std::printf("=========\nChosen Device:\n");
    {
        VkPhysicalDeviceProperties props;
        VkPhysicalDevice my_device = vkd::get_any_discrete_gpu(vki);
        vkGetPhysicalDeviceProperties(my_device, &props);
        std::printf("\t\"%s\"\n=========\n", props.deviceName);
    }
    return ctx;
}