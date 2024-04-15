#include <app/first_app.hpp>

void FirstApp::run()
{
    while(!m_my_window.should_close())
    {
        glfwPollEvents();
    }
}