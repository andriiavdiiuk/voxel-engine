#pragma once
#include "GameObject.hpp"
#include "Camera.hpp"
#include <memory>

namespace Engine
{
    class Input;


    class CameraController : public GameObject
    {
    public:
        float mouseSensitivity; 
        float speed;
        float jumpForce;
        Camera camera;
        CameraController(std::shared_ptr<Input> input);
        ~CameraController();
        virtual void update(double deltaTime) override;

    private:
        std::shared_ptr<Input> input;
    };
}