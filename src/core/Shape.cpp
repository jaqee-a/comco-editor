#include "Shape.h"
#include "core/Component.h"

namespace ComcoEditor {
  Shape::Shape() { }

  Shape::~Shape() { }

  ComcoEditor::Transform& ComcoEditor::Shape::getTransform()
  {
    return this->m_Transform;
  }

  void ComcoEditor::Shape::setTransform(ComcoEditor::Transform transform)
  {
    this->m_Transform = transform;
  }
}
