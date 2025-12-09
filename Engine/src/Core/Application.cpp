#include "Application.hpp"
#include "Window.hpp"
#include "Input/Input.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace GameEngine 
{
    Application::Application()
    {
        input = std::make_shared<Input>();
        window = std::make_shared<Window>(WindowSettings{ .width = 1280, .height = 768, .title = "title" }, input);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
    }

    void Application::run()
    {
        isRunning = true;

        while (isRunning && !window->shouldClose())
        {
            double deltaTime = calculateDeltaTime();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            update(deltaTime);
            render(deltaTime);
            window->update();
        }
        isRunning = false;
        shutdown();
    }

    double Application::calculateDeltaTime()
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        return deltaTime;
    }
}