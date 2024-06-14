#include "FileExplorer.h"
#include "core/Application.h"

#include <imgui.h>
#include <filesystem>




namespace ComcoEditor
{
  FileExplorer::FileExplorer(ImGuiLayer& imGuiLayer): Panel(imGuiLayer) {}
  FileExplorer::~FileExplorer(){}

  void FileExplorer::OnRender(Application& application)
  {
    ImGui::Begin("Explore");
    for (const auto& entry : std::filesystem::directory_iterator("./assets")) 
    {
      std::string filename = entry.path().string();
      ImGui::Selectable(filename.c_str());
      if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
      {
        ImGui::SetDragDropPayload("DND_FILENAME", filename.c_str(), sizeof(filename));
        ImGui::Text("%s", filename.c_str());
        ImGui::EndDragDropSource();
      }
    }
    ImGui::End();

  }
}
