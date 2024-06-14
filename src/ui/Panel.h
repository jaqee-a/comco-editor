#pragma once

#include "core/Application.h"
namespace ComcoEditor
{
  class Panel
  {
  public:
    Panel(ImGuiLayer& imGuiLayer): m_ImGuiLayer(imGuiLayer) {};
    ImGuiLayer& m_ImGuiLayer;
    virtual void OnRender(Application& application) {}
  private:
  };
}
