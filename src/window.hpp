#ifndef VULKANDEMO_WINDOW_HPP
#define VULKANDEMO_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace vkd
{
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        bool should_close() const;
        void update() const;
    private:
        GLFWwindow* window;
    };
}

#endif //VULKANDEMO_WINDOW_HPP