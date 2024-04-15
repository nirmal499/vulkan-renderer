#pragma once

#include <window/window.hpp>

class FirstApp
{
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        
        void run();
    private:
        Window m_my_window{WIDTH, HEIGHT, "Learning VULKAN"};
};