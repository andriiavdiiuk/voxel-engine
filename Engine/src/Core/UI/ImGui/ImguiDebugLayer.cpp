#include "ImGuiDebugLayer.hpp"
#include <imgui/imgui.h>
#include "Core/Resources/DefaultAssets.hpp"
namespace GameEngine
{
    void ImGuiDebugLayer(bool& active)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | 
                                 ImGuiWindowFlags_NoMove | 
                                 ImGuiWindowFlags_NoResize | 
                                 ImGuiWindowFlags_NoCollapse | 
                                 ImGuiWindowFlags_NoScrollbar;

        ImGuiIO& io = ImGui::GetIO();

        ImFont* font = io.Fonts->AddFontFromFileTTF(std::string(GameEngine::OpenSansTtfFontPath).c_str(), 24.0f);

        ImGui::SetNextWindowPos(ImVec2(0, 0));       
        ImGui::SetNextWindowSize(ImVec2(300, 600));    
        ImGui::SetNextWindowBgAlpha(0.3f);
        ImGui::Begin("Console", &active, flags);
      
        ImGui::PushFont(font);


        ImGui::PopFont();

        ImGui::End();
    }
}