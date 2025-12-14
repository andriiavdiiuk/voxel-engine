#include "Window.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Logger.hpp"

namespace GameEngine
{
    Window::Window(const WindowSettings& windowSettings, std::shared_ptr<Input> input) : input(std::move(input))
    {
        init();
        createWindow(windowSettings);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize OpenGL loader");
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }
    Window::~Window()
    {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    GLFWwindow* Window::getNativeWindow() const
    {
        return glfwWindow;
    }

    void Window::createWindow(const WindowSettings& windowSettings)
    {
        glfwWindow = glfwCreateWindow(windowSettings.width, windowSettings.height, windowSettings.title.c_str(), NULL, NULL);
        if (glfwWindow == NULL)
        {
            LOG_CRITICAL("Failed to create GLFW window is null");
            glfwTerminate();
            std::exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(glfwWindow);
        glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);

        glfwSetWindowUserPointer(glfwWindow, this);
        glfwSetKeyCallback(glfwWindow, keyCallback);
        glfwSetCursorPosCallback(glfwWindow, cursorPosCallback);
        glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallback);
        glfwSetScrollCallback(glfwWindow, mouseScrollCallback);
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    }

    void Window::init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Window::update()
    {
        glfwSwapBuffers(glfwWindow);

        glfwPollEvents();
        input->update();
    }


    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(glfwWindow);
    }

    const glm::ivec2 Window::getWindowSize() const
    {
        int width = 0;
        int height = 0;
        glfwGetWindowSize(glfwWindow,&width, &height);
        return { width, height };
    }

    void Window::setCursorMode(CursorModeValue value)
    {
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, static_cast<int>(value));
    }

    void Window::framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height)
    {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (!window)
        {
            LOG_ERROR("Window pointer is null");
            return;
        }

        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
        window->onWindowResize.dispatch(WindowResizeEvent(width, height));
    }

    void Window::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
    {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (!window)
        {
            LOG_ERROR("Window pointer is null");
            return;
        }

        window->input->getKeyboard().onKey(key, scancode, action, mods);
    }

    void Window::mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
    {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (!window)
        {
            LOG_ERROR("Window pointer is null");
            return;
        }

        window->input->getMouse().onKey(button, action, mods);
    }
    void Window::mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
    {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (!window)
        {
            LOG_ERROR("Window pointer is null");
            return;
        }

        window->input->getMouse().onScroll(xoffset, yoffset);
    }
    void Window::cursorPosCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
    {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        if (!window)
        {
            LOG_ERROR("Window pointer is null");
            return;
        }

        window->input->getMouse().onCursorPosition(xpos, ypos);
    }
}