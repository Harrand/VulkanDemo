#include "window.hpp"

namespace vkd
{
    Window::Window(int width, int height, const char* title): window(nullptr)
    {
        this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    }

    Window::~Window()
    {
        glfwDestroyWindow(this->window);
    }

    bool Window::should_close() const
    {
        return glfwWindowShouldClose(this->window);
    }

    void Window::update() const
    {
        glfwPollEvents();
    }
}