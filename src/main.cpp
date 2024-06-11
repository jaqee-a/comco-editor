#include "core/Application.h"
#include "core/Component.h"
#include "raylib.h"
int main(void)
{
  ComcoEditor::Application app({1220, 700, "Hello"});

  app.AppendShape();
  app.AppendShape();

  app.Run();
  app.Close();
}
