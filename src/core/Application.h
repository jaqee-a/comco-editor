#pragma once

#include "core/Shape.h"
#include <cstdint>
#include <string>
#include <vector>

namespace ComcoEditor
{
  struct ApplicationSpecification
  {
    uint32_t width;
    uint32_t height;
    std::string name;
    uint32_t fps = 60;
  };

  class Application
  {
  public:
    Application(const ApplicationSpecification& applicationSpecification);
    ~Application();

    static Application& Get() { return *s_Instance; }

    void AppendShape();
    std::vector<Shape*> GetShapes();

    void Init();
    void Run();
    void Close();

  private:
    bool m_IsRunning = false;
    ApplicationSpecification m_ApplicationSpecification;
    std::vector<Shape*> m_Shapes;
    static Application* s_Instance;
  };
}
