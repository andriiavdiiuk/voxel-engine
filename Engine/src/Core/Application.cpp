#include "Engine/Core/Application.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Core/Input/Input.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Core/UI/ImGui/ImGuiBase.hpp"
#include "Engine/Core/UI/ImGui/ImGuiDebugLayer.hpp"
namespace Engine 
{
    Application::Application()
    {
        input = std::make_shared<Input>();
        window = std::make_shared<Window>(WindowSettings{ .width = 1280, .height = 768, .title = "title" }, input);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);

        window->setCursorMode(CursorModeValue::Normal);

        initImGui(window->getNativeWindow());
    }

    Application::~Application()
    {
        shutdownImGui();
    }

    void Application::run()
    {
        isRunning = true;
        debugWindow = true;
        while (isRunning && !window->shouldClose())
        {
            double deltaTime = calculateDeltaTime();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            beginImGuiFrame();
            ImGuiDebugLayer(debugWindow);
            update(deltaTime);
            render(deltaTime);
            endImGuiFrame();
            window->update();
        }
        isRunning = false;
    }

    double Application::calculateDeltaTime()
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        return deltaTime;
    }
}