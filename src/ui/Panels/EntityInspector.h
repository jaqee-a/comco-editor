#pragma once

#include "ui/Panel.h"

namespace ComcoEditor
{
  class EntityInspector: public Panel
  {
  public:
    EntityInspector(ImGuiLayer&);
    ~EntityInspector();
    
    virtual void OnRender(Application& application) override;
  };
}
