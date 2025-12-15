#pragma once
#define GLFW_INCLUDE_NONE
#include <memory>

namespace GameEngine
{
    class Window;
    class Input;

    class Application
    {
    public:
        Application();
        virtual ~Application();
        virtual void update(double deltaTime) = 0;
        virtual void render(double deltaTime) = 0;
        virtual void shutdown() = 0;
        virtual void run();

    protected:
        std::shared_ptr<Window> window;
        std::shared_ptr<Input> input;
        bool debugWindow = false;

    private:
        bool isRunning = false;
        double lastFrameTime = 0;
        double calculateDeltaTime();
    };
}

