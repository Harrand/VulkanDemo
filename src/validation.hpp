#ifndef VULKANDEMO_VALIDATION_HPP
#define VULKANDEMO_VALIDATION_HPP
#include <vector>

namespace vkd::valid
{
    namespace detail
    {
        // TODO: constexpr when g++ has constexpr-vector support (no support in any version as of 12/04/2021)
        const std::vector<const char*> validation_layers
        {
            "VK_LAYER_KHRONOS_validation"
        };

        constexpr bool validation_layers_enabled = true;
    }

    bool confirm_layer_support();
}

#endif // VULKANDEMO_VALIDATION_HPP