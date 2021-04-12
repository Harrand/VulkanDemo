#ifndef VULKANDEMO_DEVICE_LIST_HPP
#define VULKANDEMO_DEVICE_LIST_HPP
#include "vulkan/vulkan.h"
#include <vector>
#include <initializer_list>

namespace vkd
{
    using DeviceList = std::vector<VkPhysicalDevice>;

    template<typename F>
    concept SuitablePredicate = requires(F f, VkPhysicalDevice dev)
    {
        {f(dev)} -> std::convertible_to<bool>;
    };

    DeviceList enumerate_devices(VkInstance instance);
    DeviceList filter_devices(const DeviceList& devices, std::initializer_list<SuitablePredicate auto> filters);
    VkPhysicalDevice get_any_discrete_gpu(VkInstance instance);

    namespace filters
    {
        bool is_discrete_gpu(VkPhysicalDevice dev);
    }
}
#include "device_list.inl"
#endif // VULKANDEMO_DEVICE_LIST_HPP