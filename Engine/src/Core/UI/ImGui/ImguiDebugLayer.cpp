#include <imgui/imgui.h>
#include "Engine/Core/Resources/DefaultAssets.hpp"
#include "Engine/Core/Objects/Camera.hpp"
#include <format>
namespace Engine
{
    void CameraDebug(bool& active, const Camera& camera)
    {
        if (!active)
            return;

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(600, 600));
        ImGui::SetNextWindowBgAlpha(0.3f);
        ImGui::Begin("Debug", &active, flags);

        ImGui::Text("Camera Position: X: %.2f Y: %.2f Z: %.2f",
            camera.transform.position.x,
            camera.transform.position.y,
            camera.transform.position.z);

        glm::vec3 f = camera.getForward();
        glm::vec3 absF = glm::abs(f);
        std::string direction;
        if (absF.x > absF.y && absF.x > absF.z)
            direction = (f.x > 0) ? "+X" : "-X";
        else if (absF.y > absF.x && absF.y > absF.z)
            direction = (f.y > 0) ? "+Y" : "-Y";
        else
            direction = (f.z > 0) ? "+Z" : "-Z";
        ImGui::Text("Camera Direction: %s", direction.c_str());

        ImGui::End();
    }
}