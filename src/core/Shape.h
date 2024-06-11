#pragma once

#include "core/Component.h"
namespace ComcoEditor 
{
  class Shape
  {
  public:

    ComcoEditor::Transform& getTransform();
    ComcoEditor::Sprite& getSprite();

    void setTransform(ComcoEditor::Transform);
    void setSprite(ComcoEditor::Sprite);

    Shape();
    ~Shape();

  private:
    ComcoEditor::Transform m_Transform;
    ComcoEditor::Sprite m_Sprite;
  };
}
