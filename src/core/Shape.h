#pragma once

#include "core/Component.h"
namespace ComcoEditor 
{
  class Shape
  {
  public:

    ComcoEditor::Transform& getTransform();
    void setTransform(ComcoEditor::Transform);

    Shape();
    ~Shape();

  private:
    ComcoEditor::Transform m_Transform;
  };
}
