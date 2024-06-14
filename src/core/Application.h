#pragma once

#include "utils/UUID.h"
#include <cstdint>
#include <string>
#include <entt.hpp>

namespace ComcoEditor
{
  struct ApplicationSpecification
  {
    uint32_t width;
    uint32_t height;
    std::string name;
    uint32_t fps = 60;
  };

  class Entity;
  class ImGuiLayer;

  class Application
  {
  public:
    Application(const ApplicationSpecification&);
    ~Application();

    static Application& Get() { return *s_Instance; }

    ApplicationSpecification GetApplicationSpecification(); 

    void Init();
    void Run();
    void Close();

    // TODO: Move
    Entity CreateEntity(const std::string& name);
    entt::registry m_Registry;
		std::unordered_map<UUID, Entity> m_EntityMap;
  private:
    bool m_IsRunning = false;
    ApplicationSpecification m_ApplicationSpecification;
    static Application* s_Instance;

    ImGuiLayer *m_ImGuiLayer;
  };
}
