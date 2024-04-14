#include <memory>

#include <window/window.hpp>
#include <tool/logger.hpp>

int main(int argc, char *argv[])
{
  std::unique_ptr<Window> w = std::make_unique<Window>();

  if (!w->init(640, 480, "OGL Renderer"))
  {
    Logger::log(1, "%s error: Window init error\n", __FUNCTION__);
    return -1;
  }

  w->main_loop();

  w->clean_up();

  return 0;
}