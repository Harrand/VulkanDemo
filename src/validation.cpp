#include "validation.hpp"
#include "vulkan/vulkan.h"
#include <cstdint>
#include <string>

namespace vkd::valid
{
    bool confirm_layer_support()
    {
        std::uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> avail_layers;
        avail_layers.resize(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, avail_layers.data());

        for(const char* layer_name : detail::validation_layers)
        {
            bool layer_found = false;
            for(const VkLayerProperties& property : avail_layers)
            {
                if(std::string{layer_name} == property.layerName)
                {
                    layer_found = true;
                    break;
                }
            }

            if(!layer_found)
            {
                return false;
            }
        }
        return true;
    }
}