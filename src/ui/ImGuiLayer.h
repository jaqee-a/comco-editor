#pragma once

#include <cstdint>

namespace ComcoEditor
{
  class ImGuiLayer
  {
  public:
    static void DrawMenu();
  private:
    static int32_t SelectedShapeIndex;
  };
}

