#pragma once

#include "core/Application.h"
#include "ui/Panel.h"

namespace ComcoEditor
{
  class FileExplorer: public Panel
  {
  public:
    FileExplorer(ImGuiLayer&);
    ~FileExplorer();
    
    virtual void OnRender(Application& application) override;

    // UUID GetSelectedEntityUUID();
  private:
  };
}
