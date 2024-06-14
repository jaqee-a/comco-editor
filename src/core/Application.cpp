#include "Application.h"
#include "core/Component.h"
#include "core/Renderer.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ui/ImGuiLayer.h"
#include "utils/UUID.h"
#include <cstdlib>


namespace ComcoEditor {

  Application* Application::s_Instance = nullptr;

  Application::Application(const ApplicationSpecification& applicationSpecification): m_ApplicationSpecification(applicationSpecification)
  {
    s_Instance = this;
    this->m_ImGuiLayer = new ImGuiLayer(*this);
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
    // this->m_ImGuiLayer->Init();
    m_IsRunning = true;
    while(!WindowShouldClose())
    {
      BeginDrawing();
      DrawFPS(0, 0);

      ClearBackground(RAYWHITE);

      // Update
      auto view = m_Registry.view<Rigidbody>();

      for (auto e : view)
      {
        Entity entity = { e, this };
        auto& transform = entity.GetComponent<Transform>();
        auto& rb = entity.GetComponent<Rigidbody>();

        rb.Update(GetFrameTime());

        auto& position = transform.m_Position;
        position.x += rb.m_Velocity.x;
        position.y += rb.m_Velocity.y;
      }

  
      // Render
      for(auto& [_, entity]: this->m_EntityMap)
      {
        Renderer::DrawEntity(entity);
      }

      this->m_ImGuiLayer->DrawMenu();

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
		entity.AddComponent<Rigidbody>();
		auto& tag = entity.AddComponent<Tag>();
		tag.Tag = name.empty() ? "Entity" : name;

		m_EntityMap[uuid] = entity;

		return entity;
  }

}
