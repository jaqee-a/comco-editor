#include "ImGuiLayer.h"
#include <cmath>
#include <cstdlib>
#include <imgui.h>
#include <rlImGui.h>
#include <utility>
#include "core/Application.h"
#include "core/Component.h"
#include "core/Entity.h"
#include "raylib.h"
#include "ui/Panel.h"
#include "ui/Panels/EntityInspector.h"
#include "ui/Panels/EntityList.h"
#include "ui/Panels/FileExplorer.h"

namespace ComcoEditor
{
  ImGuiLayer::ImGuiLayer(Application& application): m_Application(application)
  {
    this->CreatePanel<EntityList>(*this);
    this->CreatePanel<EntityInspector>(*this);
    this->CreatePanel<FileExplorer>(*this);
  }

  ImGuiLayer::~ImGuiLayer()
  {
    for(const auto& panel: this->m_Panels)
    {
      delete panel;
    }
  
    this->m_Panels.clear();
  }

  template<typename T, typename... Args>
  void ImGuiLayer::CreatePanel(Args&&... args)
  {
    ComcoEditor::Panel *panel = new T(std::forward<Args>(args)...);
    this->m_Panels.push_back(panel);
  }

  void ImGuiLayer::Init()
  {
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
  }

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

  void ImGuiLayer::DrawAnimationMenu()
  {
    ImGui::Begin("Animations");

    int lines = 5;
    for (int line = 0; line < lines; line++)
    {
        // Display random stuff. For the sake of this trivial demo we are using basic Button() + SameLine()
        // If you want to create your own time line for a real application you may be better off manipulating
        // the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets
        // yourself. You may also want to use the lower-level ImDrawList API.
        int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
        for (int n = 0; n < num_buttons; n++)
        {
            if (n > 0) ImGui::SameLine();
            ImGui::PushID(n + line * 1000);
            char num_buf[16];
            sprintf(num_buf, "%d", n);
            const char* label = (!(n % 15)) ? "FizzBuzz" : (!(n % 3)) ? "Fizz" : (!(n % 5)) ? "Buzz" : num_buf;
            float hue = n * 0.05f;
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
            ImGui::Button(label, ImVec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }
    }

    ImGui::End();

    ImGui::Begin("Timeline");

    // Calculate the size of the timeline
    ImVec2 timelineSize = ImGui::GetContentRegionAvail();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    
    // Draw the timeline background
    ImGui::GetWindowDrawList()->AddRectFilled(cursorPos, ImVec2(cursorPos.x + timelineSize.x, cursorPos.y + 50), IM_COL32(60, 60, 60, 255));
    
    // Draw the current time indicator
    // float indicatorPos = (rand() / RAND_MAX) * 10;
    ImGui::GetWindowDrawList()->AddLine(ImVec2(GetMouseX(), cursorPos.y), ImVec2(GetMouseX(), cursorPos.y + 50), IM_COL32(255, 0, 0, 255), 2.0f);
    
    // Here you would add code to handle keyframes and other interactive elements
    // ...

    ImGui::End();
  }

  template<class T>
  T* ImGuiLayer::GetPanel()
  {
    for (const auto& panel: this->m_Panels)
    {
      auto* derived = dynamic_cast<T*>(panel);
      if(derived != nullptr)
      {
        return derived;
      }
    }
    return nullptr;
  }

  void ImGuiLayer::DrawMenu()
  {
    rlImGuiBegin();
    
    for (const auto& panel: this->m_Panels)
    {
      panel->OnRender(this->m_Application);
    }

    this->MouseUpdate();
    ImGui::ShowDemoWindow();
    rlImGuiEnd();
  }
}
