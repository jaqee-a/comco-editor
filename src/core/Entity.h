#pragma once

#include "core/Component.h"
#include "core/Application.h"
#include <cassert>
#include <entt.hpp>

namespace ComcoEditor 
{
  class Application;

  class Entity
  {
  public:

    ComcoEditor::Transform& getTransform();
    ComcoEditor::Sprite& getSprite();

    void setTransform(ComcoEditor::Transform);
    void setSprite(ComcoEditor::Sprite);

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
