#include <window/window.hpp>

Window::Window(int w, int h, std::string title)
    : m_width(w), m_height(h), m_window_name(title)
{
    this->init_window();
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::init_window()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    /* set a "hint" for the NEXT window created*/
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, m_window_name.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_window);
}