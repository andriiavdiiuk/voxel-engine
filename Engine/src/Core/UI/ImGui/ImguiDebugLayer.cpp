#include <imgui/imgui.h>
#include "Engine/Core/Resources/DefaultAssets.hpp"
namespace Engine
{
    static ImFont* font;

    void ImGuiDebugLayer(bool& active)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoCollapse | 
                                 ImGuiWindowFlags_NoScrollbar;

        if (!font)
            font = ImGui::GetIO().Fonts->AddFontFromFileTTF(std::string(OpenSansTtfFontPath).c_str(), 24.0f);

        ImGui::SetNextWindowPos(ImVec2(0, 0));       
        ImGui::SetNextWindowSize(ImVec2(300, 600));    
        ImGui::SetNextWindowBgAlpha(0.3f);
        ImGui::Begin("Console", &active, flags);
      
        ImGui::PushFont(font);

        ImGui::LabelText("text","text");

        ImGui::PopFont();

        ImGui::End();
    }
}