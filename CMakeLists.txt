cmake_minimum_required(VERSION 3.9)
project(VulkanDemo)

set(CMAKE_CXX_STANDARD 20)

add_executable(VulkanDemo
    src/device_list.cpp
    src/device_list.inl
    src/device_list.hpp
    src/validation.cpp
    src/validation.hpp
    src/window.cpp
    src/window.hpp

    src/main.cpp)

add_subdirectory(lib)
target_compile_options(VulkanDemo PRIVATE -std=c++20 -g)
target_link_directories(VulkanDemo PRIVATE "$ENV{VK_SDK_PATH}/Lib")
target_include_directories(VulkanDemo PRIVATE "$ENV{VK_SDK_PATH}/include")
target_link_libraries(VulkanDemo PRIVATE glfw vulkan-1)
