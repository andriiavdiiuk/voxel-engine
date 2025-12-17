#pragma once
#include "GameObject.hpp"
#include "Camera.hpp"
#include <memory>

namespace Engine
{
    class Input;
    class Window;

    class CameraController : public GameObject
    {
    public:
        float mouseSensitivity; 
        float speed;
        float jumpForce;
        CameraController(std::shared_ptr<Input> input, std::shared_ptr<Window> window);
        ~CameraController();
        const Camera& getCamera() const;
        virtual void update(double deltaTime) override;

    private:
        Camera camera;
        std::shared_ptr<Input> input;
        std::shared_ptr<Window> window;
        size_t windowResizeHandle;
    };
}