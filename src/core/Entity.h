#pragma once

#include "core/Application.h"
#include <cassert>
#include <entt.hpp>

namespace ComcoEditor 
{
  class Application;

  class Entity
  {
  public:
    Entity() = default;
    Entity(entt::entity, ComcoEditor::Application*);
    Entity(const Entity&) = default;
    ~Entity();

		template<typename T>
		bool HasComponent()
		{
      return this->m_Application->m_Registry.has<T>(m_EntityHandle);
		}
  
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
      assert(!HasComponent<T>());
      return this->m_Application->m_Registry.emplace<T>(this->m_EntityHandle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent()
    {
      assert(HasComponent<T>());
      return this->m_Application->m_Registry.get<T>(this->m_EntityHandle);
    }

  private:
    ComcoEditor::Application* m_Application;
    entt::entity m_EntityHandle{ entt::null };
  };
}
