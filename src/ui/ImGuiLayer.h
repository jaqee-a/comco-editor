#pragma once

#include "core/Application.h"
#include "utils/UUID.h"

namespace ComcoEditor
{
  class ImGuiLayer
  {
  public:
    ImGuiLayer(Application&); 
    ImGuiLayer(const ImGuiLayer&) = default;
    ~ImGuiLayer(); 

    void Init();
    void DrawMenu();
  private:
    UUID m_SelectedEntityUUID = -1;
    void MouseUpdate();
    void DrawEntityListPanel();
    void DrawEntityPropertiesPanel();
    void DrawExplorerPanel();
    Application& m_Application;
  };
}

