#include <window/window.hpp>
#include <tool/logger.hpp>

bool Window::init(unsigned int width, unsigned int height, std::string title)
{
  if (!glfwInit())
  {
    Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
    return false;
  }

  /* set a "hint" for the NEXT window created*/
  // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!m_window)
  {
    Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
    glfwTerminate();
    return false;
  }

  Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      Logger::log(1, "%s: Failed to initialize GLAD\n", __FUNCTION__);
      return false;
  }

  Logger::log(1, "%s: Successfully initialized GLAD\n", __FUNCTION__);


  /* save the pointer to the instance as user pointer. m_window is a mandatory parameter in every glfwWindow functions */
  glfwSetWindowUserPointer(m_window, this);

  glfwSetWindowPosCallback(m_window, [](GLFWwindow* win, int xpos, int ypos){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_window_move_events(xpos, ypos);
  });

  glfwSetWindowIconifyCallback(m_window, [](GLFWwindow* win, int minimized){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_window_minimized_events(minimized);
  });

  glfwSetWindowMaximizeCallback(m_window, [](GLFWwindow* win, int maximized){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_window_maximized_events(maximized);
  });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow* win){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_window_close_events();
  });

  glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int width, int height){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_window_resized_events(width, height);
    glViewport(0, 0, width, height);
  });

  glfwSetKeyCallback(m_window, [](GLFWwindow *win, int key, int scancode, int action, int mods) {
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_key_events(key, scancode, action, mods);
  });

  glfwSetMouseButtonCallback(m_window, [](GLFWwindow* win, int button, int action, int mods){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_mouse_button_events(button, action, mods);
  });

  glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double xpos, double ypos){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_mouse_position_events(xpos, ypos);
  });

  glfwSetCursorEnterCallback(m_window, [](GLFWwindow* win, int enter){
    auto this_pointer_that_we_saved_earlier = static_cast<Window*>(glfwGetWindowUserPointer(win));
    this_pointer_that_we_saved_earlier->handle_mouse_enter_leave_events(enter);
  });

  return true;
}

/*
    double tap in trackpad -> right mouse pressed, right mouse released
    single tap in trackpad -> left mouse pressed, left mouse release
*/
void Window::handle_mouse_button_events(int button, int action, int mods) {
  std::string actionName;
  switch (action) {
    case GLFW_PRESS:
      actionName = "pressed";
      break;
    case GLFW_RELEASE:
      actionName = "released";
      break;
    case GLFW_REPEAT:
      actionName = "repeated";
      break;
    default:
      actionName = "invalid";
      break;
  }

  std::string mouseButtonName;
  switch(button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      mouseButtonName = "left";
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      mouseButtonName = "middle";
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      mouseButtonName = "right";
      break;
    default:
      mouseButtonName = "other";
      break;
  }

  Logger::log(1, "%s: %s mouse button (%i) %s\n", __FUNCTION__, mouseButtonName.c_str(), button, actionName.c_str());
}

/*
  It gives the mouse position when the mouse is in the GLFWwindow screen
*/
void Window::handle_mouse_position_events(double xpos, double ypos)
{
  Logger::log(1, "%s: Mouse is at position %lf/%lf\n", __FUNCTION__, xpos, ypos);
}

/*
  It is triggered when mouse leaves or enters the GLFWwindow screen
*/
void Window::handle_mouse_enter_leave_events(int enter)
{
  if (enter)
  {
    Logger::log(1, "%s: Mouse entered window\n", __FUNCTION__);
  }
  else
  {
    Logger::log(1, "%s: Mouse left window\n", __FUNCTION__);
  }
}

/*
  It is triggered when GLFWwindow screen is resized
*/
void Window::handle_window_resized_events(int width, int height)
{
  Logger::log(1, "%s: Window has been resized to %i/%i\n", __FUNCTION__, width, height);
}

/*
  It is triggered when a key is pressed and release or keep pressed{ repeated }
*/
void Window::handle_key_events(int key, int scancode, int action, int mods)
{
  std::string actionName;

  switch (action) {
    case GLFW_PRESS:
      actionName = "pressed";
      break;
    case GLFW_RELEASE:
      actionName = "released";
      break;
    case GLFW_REPEAT:
      actionName = "repeated";
      break;
    default:
      actionName = "invalid";
      break;
  }

  const char *keyName = glfwGetKeyName(key, 0);
  Logger::log(1, "%s: key %s (key %i, scancode %i) %s\n", __FUNCTION__, keyName, key, scancode, actionName.c_str());
}

/*
  It is triggered when GLFWwindow screen window is moved around
*/
void Window::handle_window_move_events(int xpos, int ypos)
{
  Logger::log(1, "%s: Window has been moved to %i/%i\n", __FUNCTION__, xpos, ypos);
}

/*
  It is triggered when GLFWwindow screen window is minimized or restore from minimized
*/
void Window::handle_window_minimized_events(int minimized)
{
  if (minimized)
  {
    Logger::log(1, "%s: Window has been minimized\n", __FUNCTION__);
  }
  else
  {
    Logger::log(1, "%s: Window has been restored\n", __FUNCTION__);
  }
}

/*
  It is triggered when GLFWwindow screen window is maximized or restore from maximized
*/
void Window::handle_window_maximized_events(int maximized)
{
  if (maximized)
  {
    Logger::log(1, "%s: Window has been maximized\n", __FUNCTION__);
  }
  else
  {
    Logger::log(1, "%s: Window has been restored\n", __FUNCTION__);
  }
}
/*
  It is triggered when GLFWwindow screen window is closed
*/
void Window::handle_window_close_events()
{
  Logger::log(1, "%s: Window got close event... bye!\n", __FUNCTION__);
}

void Window::main_loop()
{
  /*
    Before going into the loop, we will activate the wait for the vertical sync with a call to the GLFW 
    function, glfwSwapInterval(). Without waiting for it, the window might flicker, or tearing 
    might occur, as the update and buffer switch will be done as fast as possible
  */
  glfwSwapInterval(1);
  float color = 0.0f;
  while (!glfwWindowShouldClose(m_window))
  {

    color >= 1.0f ? color = 0.0f : color += 0.01f;

    glClearColor(color, color, color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_window);
    /* poll events in a loop */
    glfwPollEvents();

  }
}

void Window::clean_up()
{
  Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
  glfwDestroyWindow(m_window);
  glfwTerminate();
}