#pragma once

#include <types/types.hpp>

class Window
{
    public:
        Window(int w, int h, std::string title);
        ~Window();

        bool should_close();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

    private:
        void init_window();

        const int m_width;
        const int m_height;
        std::string m_window_name;
        GLFWwindow* m_window = nullptr;
};