
#include "core/particle.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "rlImGui.h"

#include "config.h"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace Sandbox::Menu {

    inline const int32_t s16_zero = 0, s16_max = 32767;
    inline int32_t one_drag_speed = 1;

    inline float_t gravity_force[2] = {0.0f, 0.0f}; 

    inline int32_t cloth_size[2] = {Config::CLOTH_SIZE[0], Config::CLOTH_SIZE[1]}; 
    inline int32_t spacing = Config::SPACING;

    inline float_t gravity_drag_speed = 0.01f;
    inline const float_t gravity_min = -32766, gravity_max = 32767;

    using VoidFunctionPointer = std::function<void()>;
    inline VoidFunctionPointer OnClothSizeChangeCallback = [](){};


    template <typename T>
    inline bool Value2Changed(T* local_value, T* original_value) {
        return local_value[0] != original_value[0] || local_value[1] != original_value[1];
    }

    inline void DrawMenu() {
		// start ImGui Conent
		rlImGuiBegin();

		// show ImGui Content
        if(Config::DEBUG)
		ImGui::ShowDemoWindow();

        ImGui::DragInt2("Box Position", Config::BORDER_POS, one_drag_speed, s16_zero, s16_max);
        ImGui::DragInt2("Box Size", Config::BORDER_SIZE, one_drag_speed, s16_zero, s16_max);

        if (ImGui::CollapsingHeader("Enviroment")) {
            ImGui::DragFloat2("Gravity", gravity_force, gravity_drag_speed, gravity_min, gravity_max);
            ImGui::DragInt2("Cloth Size", cloth_size, one_drag_speed, s16_zero, s16_max);
            ImGui::DragInt("Spacing", &spacing, one_drag_speed, s16_zero, s16_max);
            ImGui::DragFloat("Attraction Speed", &Config::ATTRACTION_SPEED, gravity_drag_speed, gravity_min, gravity_max);

            
            if(Value2Changed(cloth_size, Config::CLOTH_SIZE)) {
                Config::CLOTH_SIZE[0] = cloth_size[0];
                Config::CLOTH_SIZE[1] = cloth_size[1];
                OnClothSizeChangeCallback();
            }

            if(Config::SPACING != spacing) {
                Config::SPACING = spacing;
                OnClothSizeChangeCallback();
            }

            Config::GRAVITY_FORCE.x = gravity_force[0];
            Config::GRAVITY_FORCE.y = gravity_force[1];
        }
        if (ImGui::CollapsingHeader("Debug Menu")) {
            ImGui::Checkbox("Debug", &Sandbox::Config::DEBUG);
            ImGui::Checkbox("Debug Connections", &Sandbox::Config::DEBUG_CONNECTIONS);
            ImGui::Checkbox("Debug Influence Boundary", &Sandbox::Config::DEBUG_INFLUENCE);
        }

		// end ImGui Content
		rlImGuiEnd();
    }


}
