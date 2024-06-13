#include "Entity.h"

namespace ComcoEditor {
  Entity::Entity(entt::entity handle, ComcoEditor::Application* application): m_EntityHandle(handle), m_Application(application) { }

  Entity::~Entity() { }
}
