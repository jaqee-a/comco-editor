#include "ui/Panels/EntityList.h"
#include "core/Component.h"
#include "core/Entity.h"
#include "ui/ImGuiLayer.h"
#include "ui/Panel.h"

#include <imgui.h>

namespace ComcoEditor
{
  EntityList::EntityList(ImGuiLayer& imGuiLayer): Panel(imGuiLayer){}
  EntityList::~EntityList(){}

  // UUID EntityList::GetSelectedEntityUUID()
  // {
  //   return this->m_SelectedEntityUUID;
  // }

  void EntityList::OnRender(Application& application)
  {
    ImGui::Begin("Entitys List");
      if (ImGui::BeginMenu("Add"))
      {
        if(ImGui::MenuItem("New", NULL, false, true))
        {
          application.CreateEntity("Hello Entity").AddComponent<ComcoEditor::Sprite>();
        }
        ImGui::EndMenu();
      }

      for(auto& [uuid, entity]: application.m_EntityMap)
      {
        Tag tag = entity.GetComponent<Tag>();
        std::string name = tag.Tag + " (" + std::to_string(uuid) + ")";
        if(ImGui::Selectable(name.c_str(), this->m_ImGuiLayer.m_SelectedEntityUUID == uuid))
        {
          this->m_ImGuiLayer.m_SelectedEntityUUID = uuid;
        }
      }
      ImGui::End();

  }
}
