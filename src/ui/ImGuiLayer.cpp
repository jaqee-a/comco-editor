#include "ImGuiLayer.h"

#include <imgui.h>
#include <iostream>
#include <rlImGui.h>
#include <sstream>
#include "core/Application.h"
#include "core/Shape.h"
#include "raylib.h"

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
    // if (ImGui::BeginMenuBar())
    // {
      if (ImGui::BeginMenu("Add"))
      {
        if(ImGui::MenuItem("New", NULL, false, true))
        {
          application.AppendShape();
        }
        ImGui::EndMenu();
      }
    // }

    for (size_t i = 0; i < shapes.size(); ++i) {
        std::stringstream ss;
    ss<<i;
        if(ImGui::Selectable(ss.str().c_str(), SelectedShapeIndex == i))
        {
          SelectedShapeIndex = i;
        }
    }
    ImGui::End();

    ImGui::ShowDemoWindow();

    // Right panels
    ImGui::Begin("Shape Information");
    if (SelectedShapeIndex != -1) {
        ComcoEditor::Shape* selectedShape = shapes[SelectedShapeIndex];
        ComcoEditor::Transform* transform = &selectedShape->getTransform();
        ComcoEditor::Sprite* sprite = &selectedShape->getSprite();
        // ImGui::Text("Name: %s", selectedShape.name.c_str());
        
        ImGui::SliderFloat2("Position", (float*)(&transform->m_Position), 0.0f, 200.0f);
        ImGui::SliderFloat2("Size", (float*)(&transform->m_Scale), 0.0f, 200.0f);
        ImGui::ColorEdit4("Color", (float*)(&sprite->m_Color));
    } else {
        ImGui::Text("No shape selected");
    }
    ImGui::End();

    rlImGuiEnd();

  }



}
