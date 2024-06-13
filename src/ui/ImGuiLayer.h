#pragma once

#include "utils/UUID.h"

namespace ComcoEditor
{
  class ImGuiLayer
  {
  public:
    static void DrawMenu();
  private:
    static UUID SelectedEntityUUID;
  };
}

