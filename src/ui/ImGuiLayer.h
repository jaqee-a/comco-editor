#pragma once

#include "core/Application.h"
#include "ui/Panel.h"
#include <vector>

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

    template<typename T, typename... Args>
    void CreatePanel(Args&&... args);

    template<typename T>
    T* GetPanel();
    
    UUID m_SelectedEntityUUID = -1;
  private:
    void MouseUpdate();
    void DrawEntityListPanel();
    void DrawEntityPropertiesPanel();
    void DrawAnimationMenu();
    void DrawExplorerPanel();
    Application& m_Application;

    std::vector<Panel*> m_Panels;
  };
}

