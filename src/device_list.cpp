#include "device_list.hpp"
#include <cstdint>
#include <cassert>

namespace vkd
{
    DeviceList enumerate_devices(VkInstance instance)
    {
        DeviceList devs;
        std::uint32_t device_count;
        vkEnumeratePhysicalDevices(instance, &device_count, nullptr);
        devs.resize(device_count);
        vkEnumeratePhysicalDevices(instance, &device_count, devs.data());
        return devs;
    }

    VkPhysicalDevice get_any_discrete_gpu(VkInstance instance)
    {
        DeviceList gpus = enumerate_devices(instance);
        gpus = filter_devices(gpus, {filters::is_discrete_gpu, filters::has_graphics_queue});
        assert(!gpus.empty());
        return gpus[0];
    }

    namespace filters
    {
        bool is_discrete_gpu(VkPhysicalDevice dev)
        {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(dev, &props);
            return props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
        }

        bool has_graphics_queue(VkPhysicalDevice dev)
        {
            std::vector<VkQueueFamilyProperties> fam_props;
            std::uint32_t fam_prop_count;
            vkGetPhysicalDeviceQueueFamilyProperties(dev, &fam_prop_count, nullptr);
            fam_props.resize(fam_prop_count);
            vkGetPhysicalDeviceQueueFamilyProperties(dev, &fam_prop_count, fam_props.data());
            for(const VkQueueFamilyProperties& prop : fam_props)
            {
                if(prop.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    return true;
                }
            }
            return false;
        }
    }
}