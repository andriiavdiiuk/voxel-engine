#include "Engine/Core/Objects/CameraController.hpp"
#include <glm/glm.hpp>
#include "Engine/Core/Input/Input.hpp"
#include "Engine/Core/Logger.hpp"
#define GLM_ENABLE_EXPERIMENTAL
namespace Engine
{
    CameraController::CameraController(std::shared_ptr<Input> input) :
        camera(Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
        speed(20.0f),
        jumpForce(10.0f),
        mouseSensitivity(0.5),
        input(std::move(input))
    {
    }
    CameraController::~CameraController()
    {

    }
    void CameraController::update(double deltaTime)
    {
        const Keyboard& keyboard = input->getKeyboard();
        glm::vec3 movement = glm::vec3(0.0f);

        if (keyboard.isKeyDown(Key::W))
        {
            movement += camera.getForward() * speed * (float)deltaTime  ;//Forward 
        }

        if (keyboard.isKeyDown(Key::S))
        {
            movement -= camera.getForward() * speed * (float)deltaTime;  //Backwards
        }

        if (keyboard.isKeyDown(Key::A))
        {
            movement -= camera.getRight() * speed * (float)deltaTime;  // Left
        }

        if (keyboard.isKeyDown(Key::D))
        {
            movement += camera.getRight() * speed * (float)deltaTime;  // Right
        }

        camera.transform.position += movement;

        const Mouse& mouse = input->getMouse();
        const glm::vec2 delta = mouse.getDeltaMovement();
        double deltaX = delta.x * mouseSensitivity;
        double deltaY = delta.y * mouseSensitivity;
        if (deltaX != 0 || deltaY != 0)
        {
            camera.rotate(deltaX, deltaY);
        }

        camera.update(deltaTime);
    }
}