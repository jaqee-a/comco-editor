#include "core/Application.h"
int main(void)
{
  ComcoEditor::Application app({1420, 700, "Comco Editor"});
  app.Run();
  app.Close();
}
