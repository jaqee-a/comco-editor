#include "ImGuiLayer.h"

#include <cmath>
#include <imgui.h>
#include <rlImGui.h>
#include <string>
#include "core/Application.h"
#include "core/Component.h"
#include "core/Entity.h"

namespace ComcoEditor
{
  UUID ImGuiLayer::SelectedEntityUUID = -1;

  void ImGuiLayer::DrawMenu()
  {
    rlImGuiBegin();

    ComcoEditor::Application& application = ComcoEditor::Application::Get();
    ApplicationSpecification applicationSpecification = application.GetApplicationSpecification();

    // Left panel
    ImGui::Begin("Entitys List");
    // if (ImGui::BeginMenuBar())
    // {
      if (ImGui::BeginMenu("Add"))
      {
        if(ImGui::MenuItem("New", NULL, false, true))
        {
          application.CreateEntity("Hello Entity").AddComponent<ComcoEditor::Sprite>();
        }
        ImGui::EndMenu();
      }
    // }

    for(auto& [uuid, entity]: application.m_EntityMap)
    {
      Tag tag = entity.GetComponent<Tag>();
      std::string name = tag.Tag + " (" + std::to_string(uuid) + ")";
      if(ImGui::Selectable(name.c_str(), SelectedEntityUUID == uuid))
      {
        SelectedEntityUUID = uuid;
      }
    }
    ImGui::End();

    ImGui::ShowDemoWindow();

    // Right panels
    ImGui::Begin("Entity Information");
    if (SelectedEntityUUID != -1) {
        ComcoEditor::Entity* selectedEntity = &application.m_EntityMap[SelectedEntityUUID];

        ComcoEditor::Tag tag = selectedEntity->GetComponent<ComcoEditor::Tag>();
        ImGui::Text("%s", tag.Tag.c_str());
        
        if(selectedEntity->HasComponent<ComcoEditor::Transform>() && ImGui::CollapsingHeader("Transform"))
        {
          ComcoEditor::Transform* transform = &selectedEntity->GetComponent<ComcoEditor::Transform>();

          ImGui::DragFloat2("Position", (float*)(&transform->m_Position));
          ImGui::DragFloat2("Size", (float*)(&transform->m_Scale));
        }

        if(selectedEntity->HasComponent<ComcoEditor::Sprite>() && ImGui::CollapsingHeader("Sprite"))
        {
          ComcoEditor::Sprite* sprite = &selectedEntity->GetComponent<ComcoEditor::Sprite>();

          ImGui::ColorEdit4("Color", (float*)(&sprite->m_Color));

          if(rlImGuiImageButtonSize("Load new image", &sprite->m_Texture, {50, 50}))
          {
            sprite->Unload();
          }

        }

    } else {
        ImGui::Text("No entity selected");
    }
    ImGui::End();

    rlImGuiEnd();

  }



}
