#pragma once

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace GameEngine
{
    void initImGui(GLFWwindow* window);

    void beginImGuiFrame();

    void endImGuiFrame();

    void shutdownImGui();
}