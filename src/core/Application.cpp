#include "Application.h"
#include "core/Component.h"
#include "core/Renderer.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ui/ImGuiLayer.h"
#include "utils/UUID.h"
#include <cstdlib>
#include "Entity.h"


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

  ApplicationSpecification Application::GetApplicationSpecification()
  {
    return this->m_ApplicationSpecification;
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
    ImGuiLayer::Init();
    m_IsRunning = true;
    while(!WindowShouldClose())
    {
      BeginDrawing();
      DrawFPS(0, 0);

      ClearBackground(RAYWHITE);
  
      for(auto& [_, entity]: this->m_EntityMap)
      {
        Renderer::DrawEntity(entity);
      }

      ImGuiLayer::DrawMenu();

      EndDrawing();
    }
  }

  void Application::Close()
  {
    m_IsRunning = false;

    for(auto& [_, entity]: this->m_EntityMap)
    {
      Renderer::DrawEntity(entity);
    }

    this->m_EntityMap.clear();
    
    rlImGuiShutdown();
    CloseWindow();
  }


  ComcoEditor::Entity Application::CreateEntity(const std::string& name)
  {
		ComcoEditor::Entity entity = { this->m_Registry.create(), this };
    UUID uuid = UUID();
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<Transform>();
		auto& tag = entity.AddComponent<Tag>();
		tag.Tag = name.empty() ? "Entity" : name;

		m_EntityMap[uuid] = entity;

		return entity;
  }

}
