#pragma once

#include "core/Application.h"
#include "ui/Panel.h"

namespace ComcoEditor
{
  class EntityList: public Panel
  {
  public:
    EntityList(ImGuiLayer&);
    ~EntityList();
    
    virtual void OnRender(Application& application) override;

    // UUID GetSelectedEntityUUID();
  private:
  };
}
