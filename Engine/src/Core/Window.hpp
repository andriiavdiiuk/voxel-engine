#pragma once
#include <functional>
#include <string>
#include "Core/Events/EventDispatcher.hpp"
#include <glm/glm.hpp>
#include <memory>

struct GLFWwindow;

namespace GameEngine
{
    struct WindowSettings
    {
        unsigned int width, height;
        std::string title;
    };

    struct WindowResizeEvent
    {
        unsigned int width, height;
    };


    class Input;

    class Window 
    {
    public:
        Window(const WindowSettings& windowSettings, std::shared_ptr<Input> input);
        ~Window();
        void update();
        bool shouldClose() const;
        GLFWwindow* getNativeWindow() const;
        const glm::ivec2 getWindowSize() const;
        EventDispatcher<WindowResizeEvent> onWindowResize;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

    private:
        GLFWwindow* glfwWindow = nullptr;
        std::shared_ptr<Input> input;
       
        void init();
        void createWindow(const WindowSettings& windowSettings);
        static void framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
        static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
        static void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
        static void cursorPosCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
    };
}