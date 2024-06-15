#include "ui/Panels/Animator.h"
#include "core/AnimationNode.h"
#include "core/Component.h"
#include "core/Entity.h"
#include "core/Filesystem.h"
#include "entt.hpp"
#include "raylib.h"
#include "ui/ImGuiLayer.h"
#include "ui/Panel.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <imgui.h>
#include <vector>

namespace ComcoEditor
{
  Animator::Animator(ImGuiLayer& imGuiLayer): Panel(imGuiLayer) {}
  Animator::~Animator(){}
  std::pair<AnimationNode*, AnimationNode*> Animator::GetNextAnimationNode(UUID entityUUID)
  {
    AnimationNode *prevNode = nullptr, *nextNode = nullptr;
    for(auto node: this->m_AnimationNodes)
    {
      if(node->m_EntityUUID != entityUUID) continue;

      if(node->m_Timestamp < this->m_CurrentTime && (prevNode == nullptr || prevNode->m_Timestamp < node->m_Timestamp))
      { prevNode = node; }

      if(node->m_Timestamp > this->m_CurrentTime && (nextNode == nullptr || nextNode->m_Timestamp > node->m_Timestamp))
      { nextNode = node; }
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
      ImVec2 position = ImVec2(cursorPos.x + (node->m_Timestamp / 10) * timelineSize.x, cursorPos.y + 75);
      ImGui::GetWindowDrawList()->AddRectFilled(position, ImVec2(position.x + 2, position.y + 2), IM_COL32(255, 0, 0, 255));


      // Play animation
      if(!m_IsPlaying) continue;
      ComcoEditor::Entity* selectedEntity = &application.m_EntityMap[node->m_EntityUUID];
      auto nodes = this->GetNextAnimationNode(node->m_EntityUUID);
      if(nodes.first != nullptr)
      {
        ComcoEditor::Transform* transform = &selectedEntity->GetComponent<ComcoEditor::Transform>();
        Vector2 newPosition = nodes.first->m_Transform.m_Position;

        if(nodes.second != nullptr)
        {
          Vector2 nextPosition = nodes.second->m_Transform.m_Position;
          float_t startStamp = nodes.first->m_Timestamp;
          float_t endStamp = nodes.second->m_Timestamp - startStamp;
          float_t t = (this->m_CurrentTime - startStamp) / endStamp;

          newPosition.x += (nextPosition.x - newPosition.x) * t;
          newPosition.y += (nextPosition.y - newPosition.y) * t;

        }

        transform->m_Position = newPosition;
      }
    }
    
    float indicatorPos = (this->m_CurrentTime / 10) * timelineSize.x;
    ImGui::GetWindowDrawList()->AddLine(ImVec2(cursorPos.x + indicatorPos, cursorPos.y + 50), ImVec2(cursorPos.x + indicatorPos, cursorPos.y + 100), IM_COL32(255, 0, 0, 255), 2.0f);

    ImGui::SameLine();
    ImGui::BeginDisabled(this->m_ImGuiLayer.m_SelectedEntityUUID == -1);
    ImGui::Button("New");
    ImGui::EndDisabled();
    ImGui::SameLine();
    if(ImGui::Button("Pause")) this->m_IsPlaying = false;
    ImGui::SameLine();
    if(ImGui::Button("Play")) this->m_IsPlaying = true;
    ImGui::SameLine();
    if(ImGui::Button("Reset")) this->m_CurrentTime = 0;
    ImGui::SameLine();
    if(ImGui::Button("Save")) {
      AnimationNode* anim = new AnimationNode[this->m_AnimationNodes.size()];

      for(int i=0;i<this->m_AnimationNodes.size(); ++i)
        {
          anim[i] = *this->m_AnimationNodes[i];
        }

      ComcoEditor::SaveToBinaryFile<AnimationNode>(anim, sizeof(AnimationNode), this->m_AnimationNodes.size(), "Animation.anim");
    }
    ImGui::BeginDisabled(this->m_ImGuiLayer.m_SelectedEntityUUID == -1);
    ImGui::SameLine();
    if(ImGui::Button("Load")){
      size_t length;
      AnimationNode* loadedAnimation = ComcoEditor::LoadBinaryFile<AnimationNode>("Animation.anim", length);

      for(const auto& node: this->m_AnimationNodes)
        delete node;
        
      this->m_AnimationNodes.clear();

      for(int i=0; i<length;++i)
      {
        // std::cout << (loadedAnimation+i)->m_Transform.m_Position.x << std::endl;
        (loadedAnimation+i)->m_EntityUUID = this->m_ImGuiLayer.m_SelectedEntityUUID;
        this->m_AnimationNodes.push_back(loadedAnimation+i);
      }
    }
    ImGui::SameLine();
    if(ImGui::Button("Snapshot"))
    {
      ComcoEditor::Entity* selectedEntity = &application.m_EntityMap[this->m_ImGuiLayer.m_SelectedEntityUUID];

      ComcoEditor::Transform transform = selectedEntity->GetComponent<ComcoEditor::Transform>();
      this->m_AnimationNodes.push_back(new AnimationNode({selectedEntity->GetComponent<IDComponent>().ID, this->m_CurrentTime, {transform.m_Position}}));
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
