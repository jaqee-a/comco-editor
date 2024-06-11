#include "core/Renderer.h"
#include "raylib.h"

namespace ComcoEditor {
  void Renderer::DrawShape(ComcoEditor::Shape shape)
  {
    Transform transform = shape.getTransform();

    Vector2 position = transform.m_Position;
    Vector2 scale = transform.m_Scale;

    DrawRectangle(position.x, position.y, scale.x, scale.y, RED);
  }
}
