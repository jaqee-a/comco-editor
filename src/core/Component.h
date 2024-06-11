#pragma once

#include "raylib.h"

namespace ComcoEditor 
{

  struct Transform
  {
    Vector2 m_Position;
    Vector2 m_Rotation;
    Vector2 m_Scale;
  };

  struct Sprite
  {
    Vector4 m_Color{0.0f, 0.0f, 0.0f, 1.0f};
  };

}
