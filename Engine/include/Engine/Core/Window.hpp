#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Engine/Core/Events/EventDispatcher.hpp"
#include <glm/glm.hpp>
#include <memory>

struct GLFWwindow;

namespace Engine
{
    enum class CursorModeValue : int
    {
        Normal = GLFW_CURSOR_NORMAL,
        Hidden = GLFW_CURSOR_HIDDEN,
        Disabled = GLFW_CURSOR_DISABLED,
        Captured = GLFW_CURSOR_CAPTURED,
    };

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
        bool shouldClose() const;
        GLFWwindow* getNativeWindow() const;
        const glm::ivec2 getWindowSize() const;
        void setCursorMode(CursorModeValue value);
        void pollEvents();
        void swapBuffer();

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