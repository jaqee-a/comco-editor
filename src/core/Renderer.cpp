#include "core/Renderer.h"
#include "raylib.h"
#include <iostream>

namespace ComcoEditor {
  void Renderer::DrawShape(ComcoEditor::Shape shape)
  {
    Transform transform = shape.getTransform();
    Sprite sprite = shape.getSprite();

    Vector2 position = transform.m_Position;
    Vector2 scale = transform.m_Scale;

    DrawRectangle(position.x, position.y, scale.x, scale.y, 
                  Color(sprite.m_Color.x*255, 
                        sprite.m_Color.y*255, 
                        sprite.m_Color.z*255, 
                        sprite.m_Color.w*255));
  }
}
