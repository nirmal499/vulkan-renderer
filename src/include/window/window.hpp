#pragma once

#include <types/types.hpp>

class Window
{
    public:
        bool init(unsigned int width, unsigned int height, std::string title);
        void main_loop();
        void clean_up();
    
    private:
        void handle_window_move_events(int xpos, int ypos);
        void handle_window_minimized_events(int minimized);
        void handle_window_maximized_events(int maximized);
        void handle_window_close_events();
        void handle_window_resized_events(int width, int height);
        void handle_mouse_button_events(int button, int action, int mods);
        void handle_mouse_position_events(double xpos, double ypos);
        void handle_mouse_enter_leave_events(int enter);
        void handle_key_events(int key, int scancode, int action, int mods);
    private:
        GLFWwindow* m_window = nullptr;
};