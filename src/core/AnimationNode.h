#pragma once

#include "core/Component.h"
#include "utils/UUID.h"
namespace ComcoEditor
{
  struct AnimationNode
  {
    UUID m_EntityUUID = -1;
    float m_Timestamp = 0.f;
    ComcoEditor::Transform m_Transform;
  };
}
