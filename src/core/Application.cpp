#include "Application.h"
#include "core/Renderer.h"
#include "core/Shape.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ui/ImGuiLayer.h"
#include <cstdlib>


namespace ComcoEditor {

  Application* Application::s_Instance = nullptr;

  Application::Application(const ApplicationSpecification& applicationSpecification): m_ApplicationSpecification(applicationSpecification)
  {
    s_Instance = this;
    Init();
  }

  Application::~Application()
  {
    s_Instance = nullptr;
  }

  void Application::AppendShape()
  {
    Shape *shape = new Shape();
    shape->setTransform({
      {(rand() / (float) RAND_MAX) * 500, (rand() / (float) RAND_MAX) * 500},
      {0, 0},
      {50, 50}
    });
    this->m_Shapes.push_back(shape);
  }

  std::vector<Shape*> Application::GetShapes()
  {
    return this->m_Shapes;
  }

  void Application::Init()
  {
    InitWindow(m_ApplicationSpecification.width, 
               m_ApplicationSpecification.height,
               m_ApplicationSpecification.name.c_str());
    rlImGuiSetup(true);
    SetTargetFPS(m_ApplicationSpecification.fps);
  }

  void Application::Run()
  {
    m_IsRunning = true;
    while(!WindowShouldClose())
    {
      BeginDrawing();
      DrawFPS(0, 0);

      ClearBackground(BLACK);
  
      // Draw shapes

      for(auto& shape: this->m_Shapes)
      {
        Renderer::DrawShape(*shape);
      }

      ImGuiLayer::DrawMenu();

      EndDrawing();
    }
  }

  void Application::Close()
  {
    m_IsRunning = false;

    for(auto& shape: this->m_Shapes)
    {
      delete shape;
    }

    this->m_Shapes.clear();
    
    rlImGuiShutdown();
    CloseWindow();
  }

}
