#include "ImGuiLayer.h"
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <imgui.h>
#include <rlImGui.h>
#include <string>
#include "core/Application.h"
#include "core/Component.h"
#include "core/Entity.h"

namespace ComcoEditor
{
  ImGuiLayer::ImGuiLayer(Application& application): m_Application(application)
  { }

  void ImGuiLayer::MouseUpdate()
  {
    for(auto [uuid, entity]: this->m_Application.m_EntityMap)
    {
      if(!entity.HasComponent<Transform>()) continue;
      Transform transform = entity.GetComponent<Transform>();
      Vector2 position = transform.m_Position;
      Vector2 scale = transform.m_Scale;
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        if(mouseX >= position.x && mouseY >= position.y && mouseX <= position.x + scale.x && mouseY <= position.y + scale.y)
        {
          m_SelectedEntityUUID = uuid;
          break;
        }
      }
    }
  }
  
  void ImGuiLayer::DrawEntityListPanel()
  {
    ImGui::Begin("Entitys List");
      // if (ImGui::BeginMenuBar())
      // {
        if (ImGui::BeginMenu("Add"))
        {
          if(ImGui::MenuItem("New", NULL, false, true))
          {
            this->m_Application.CreateEntity("Hello Entity").AddComponent<ComcoEditor::Sprite>();
          }
          ImGui::EndMenu();
        }
      // }

      for(auto& [uuid, entity]: this->m_Application.m_EntityMap)
      {
        Tag tag = entity.GetComponent<Tag>();
        std::string name = tag.Tag + " (" + std::to_string(uuid) + ")";
        if(ImGui::Selectable(name.c_str(), m_SelectedEntityUUID == uuid))
        {
          m_SelectedEntityUUID = uuid;
        }
      }
      ImGui::End();
  }

  void ImGuiLayer::DrawEntityPropertiesPanel()
  {
    ImGui::Begin("Entity Information");
    if (m_SelectedEntityUUID != -1) 
    {
      ComcoEditor::Entity* selectedEntity = &this->m_Application.m_EntityMap[m_SelectedEntityUUID];

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

        if (ImGui::BeginDragDropTarget())
        {
          if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_FILENAME"))
          {
            const char* filename = (const char*)payload->Data;
            sprite->Unload();
            sprite->Load(filename);
          }
          ImGui::EndDragDropTarget();
        }
      }

      if(selectedEntity->HasComponent<ComcoEditor::Rigidbody>() && ImGui::CollapsingHeader("Rigidbody"))
      {
        ComcoEditor::Rigidbody* rigidbody = &selectedEntity->GetComponent<ComcoEditor::Rigidbody>();
        ImGui::DragFloat2("Velocity", (float*)(&rigidbody->m_Velocity));
        ImGui::DragFloat2("Acceleration", (float*)(&rigidbody->m_Acceleration)); 
        ImGui::DragFloat("Mass", &rigidbody->m_Mass); 
        ImGui::Checkbox("Use Gravity", &rigidbody->m_UseGravity); 
        ImGui::Checkbox("Use Drag", &rigidbody->m_UseDrag); 
        ImGui::DragFloat("Drag", &rigidbody->m_Drag, 0.01f, 0.f, 1.f);
      }

      // if (ImGui::Button("Select.."))
      //   ImGui::OpenPopup("my_select_popup");

      // ImGui::SameLine();
      // if (ImGui::BeginPopup("my_select_popup"))
      // {
      //   ImGui::SeparatorText("Components");
      //   for (int i = 0; i < 10; i++)
      //   {
      //     if(ImGui::Selectable(std::to_string(i).c_str()))
      //     {
      //     }
      //   }
      //   ImGui::EndPopup();
      // }
      
    } else {
        ImGui::Text("No entity selected");
    }
    ImGui::End();
  }

  void ImGuiLayer::DrawExplorerPanel()
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



  void ImGuiLayer::DrawMenu()
  {
    rlImGuiBegin();
    ImGui::StyleColorsDark();
    this->MouseUpdate();
    this->DrawEntityListPanel();
    this->DrawEntityPropertiesPanel();
    this->DrawExplorerPanel();
    ImGui::ShowDemoWindow();
    rlImGuiEnd();
  }
}
