#include "ui/Panels/Animator.h"
#include "core/AnimationNode.h"
#include "core/Component.h"
#include "core/Entity.h"
#include "core/Filesystem.h"
#include "entt.hpp"
#include "raylib.h"
#include "ui/ImGuiLayer.h"
#include "ui/Panel.h"

#include <cmath>
#include <cstring>
#include <imgui.h>
#include <vector>

namespace ComcoEditor
{
  Animator::Animator(ImGuiLayer& imGuiLayer): Panel(imGuiLayer) {}
  Animator::~Animator(){}
  std::pair<AnimationNode, AnimationNode> Animator::GetNextAnimationNode(UUID entityUUID, bool& hasPrev, bool& hasNext)
  {
    AnimationNode prevNode, nextNode;
    for(auto node: this->m_AnimationNodes)
    {
      if(node.m_EntityUUID != entityUUID) continue;

      if(node.m_Timestamp < this->m_CurrentTime && (!hasPrev || prevNode.m_Timestamp < node.m_Timestamp))
      { prevNode = node; hasPrev = true; }

      if(node.m_Timestamp > this->m_CurrentTime && (!hasNext || nextNode.m_Timestamp > node.m_Timestamp))
      { nextNode = node; hasNext = true;}
    }
    return {prevNode, nextNode};
  }

  void Animator::OnRender(Application& application)
  {
    ImGui::Begin("Animator");
  
    ImVec2 timelineSize = ImGui::GetContentRegionAvail();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
  
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(cursorPos.x, cursorPos.y + 50), ImVec2(cursorPos.x + timelineSize.x, cursorPos.y + 100), IM_COL32(60, 60, 60, 255));

    for(auto node: this->m_AnimationNodes)
    {
      ImVec2 position = ImVec2(cursorPos.x + (node.m_Timestamp / 10) * timelineSize.x, cursorPos.y + 75);
      ImGui::GetWindowDrawList()->AddRectFilled(position, ImVec2(position.x + 2, position.y + 2), IM_COL32(255, 0, 0, 255));


      // Play animation
      if(!m_IsPlaying || m_Record) continue;
      ComcoEditor::Entity* selectedEntity = &application.m_EntityMap[node.m_EntityUUID];
      bool hasNext = false, hasPrev = false;
      auto nodes = this->GetNextAnimationNode(node.m_EntityUUID, hasPrev, hasNext);
      if(hasPrev)
      {
        ComcoEditor::Transform* transform = &selectedEntity->GetComponent<ComcoEditor::Transform>();
        Vector2 newPosition = nodes.first.m_Transform.m_Position;

        if(hasNext)
        {
          Vector2 nextPosition = nodes.second.m_Transform.m_Position;
          float_t startStamp = nodes.first.m_Timestamp;
          float_t endStamp = nodes.second.m_Timestamp - startStamp;
          float_t t = (this->m_CurrentTime - startStamp) / endStamp;

          newPosition.x += (nextPosition.x - newPosition.x) * t;
          newPosition.y += (nextPosition.y - newPosition.y) * t;

        }

        transform->m_Position = newPosition;
      }
    }
    
    float indicatorPos = (this->m_CurrentTime / 10) * timelineSize.x;
    ImGui::GetWindowDrawList()->AddLine(ImVec2(cursorPos.x + indicatorPos, cursorPos.y + 50), ImVec2(cursorPos.x + indicatorPos, cursorPos.y + 100), IM_COL32(255, 0, 0, 255), 2.0f);

    // ImGui::SameLine();
    // ImGui::BeginDisabled(this->m_ImGuiLayer.m_SelectedEntityUUID == -1);
    // ImGui::Button("New");
    // ImGui::EndDisabled();
    ImGui::SameLine();
    if(ImGui::Button("Pause")) this->m_IsPlaying = false;
    ImGui::SameLine();
    if(ImGui::Button("Play")) this->m_IsPlaying = true;
    ImGui::SameLine();
    if(ImGui::Button("Reset")) this->m_CurrentTime = 0;
    ImGui::SameLine();
    if(ImGui::Button("Clear")) this->m_AnimationNodes.clear();
    ImGui::SameLine();
    if(ImGui::Button("Save")) {
      ComcoEditor::SaveToBinaryFile<AnimationNode>(this->m_AnimationNodes.data(), sizeof(AnimationNode), this->m_AnimationNodes.size(), "Animation.anim");
    }
    ImGui::BeginDisabled(this->m_ImGuiLayer.m_SelectedEntityUUID == -1);
    ImGui::SameLine();
    if(ImGui::Button("Load")){
      size_t length;
      AnimationNode* loadedAnimation = ComcoEditor::LoadBinaryFile<AnimationNode>("Animation.anim", length);

      this->m_AnimationNodes.clear();

      for(int i=0; i<length;++i)
      {
        (loadedAnimation+i)->m_EntityUUID = this->m_ImGuiLayer.m_SelectedEntityUUID;
        this->m_AnimationNodes.push_back(*(loadedAnimation+i));
      }
    }
    ImGui::SameLine();
    if(ImGui::Button("Snapshot") || m_Record)
    {
      ComcoEditor::Entity* selectedEntity = &application.m_EntityMap[this->m_ImGuiLayer.m_SelectedEntityUUID];

      ComcoEditor::Transform transform = selectedEntity->GetComponent<ComcoEditor::Transform>();
      this->m_AnimationNodes.push_back({selectedEntity->GetComponent<IDComponent>().ID, this->m_CurrentTime, {transform.m_Position}});
    }

    ImGui::SameLine();
    if(ImGui::Button("Record")) {
      this->m_IsPlaying = !this->m_IsPlaying;
      this->m_Record = !this->m_Record;
    }

    ImGui::EndDisabled();
    this->m_CurrentTime += GetFrameTime() * this->m_IsPlaying;
        if(this->m_IsPlaying) std::cout <<"TIME " << this->m_CurrentTime << std::endl;


    if(this->m_CurrentTime > 10.f)
    {
      this->m_CurrentTime = 0;
    }
    

    ImGui::End();
  }
}
