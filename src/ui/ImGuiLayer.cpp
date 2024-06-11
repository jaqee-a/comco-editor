#include "ImGuiLayer.h"

#include <imgui.h>
#include <rlImGui.h>
#include <sstream>
#include "core/Application.h"
#include "core/Shape.h"

namespace ComcoEditor
{

  int32_t ImGuiLayer::SelectedShapeIndex = -1;

  void ImGuiLayer::DrawMenu()
  {
    rlImGuiBegin();

    ComcoEditor::Application& application = ComcoEditor::Application::Get();
    std::vector<ComcoEditor::Shape*> shapes = application.GetShapes();

    // Left panel
    ImGui::Begin("Shapes List");
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::stringstream ss;
    ss<<i;
        if(ImGui::Selectable(ss.str().c_str(), SelectedShapeIndex == i))
        {
          SelectedShapeIndex = i;
        }
    }
    ImGui::End();

    // Right panels
    ImGui::Begin("Shape Information");
    if (SelectedShapeIndex != -1) {
        ComcoEditor::Shape* selectedShape = shapes[SelectedShapeIndex];
        ComcoEditor::Transform& transform = selectedShape->getTransform();
        // ImGui::Text("Name: %s", selectedShape.name.c_str());
        
        ImGui::SliderFloat2("Position", (float*)(&transform.m_Position), 0.0f, 200.0f);
        ImGui::SliderFloat2("Size", (float*)(&transform.m_Scale), 1.0f, 200.0f);
        // ImGui::ColorEdit3("Color", (float*)&selectedShape.color);
    } else {
        ImGui::Text("No shape selected");
    }
    ImGui::End();

    rlImGuiEnd();

  }



}
