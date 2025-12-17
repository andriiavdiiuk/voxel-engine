#include "Engine/Core/Objects/CameraController.hpp"
#include <glm/glm.hpp>
#include "Engine/Core/Input/Input.hpp"
#include "Engine/Core/Logger.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "Engine/Core/Window.hpp"
using namespace std::placeholders;

namespace Engine
{
    CameraController::CameraController(std::shared_ptr<Input> input, std::shared_ptr<Window> window) :
        camera(Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(window->getWindowSize()))),
        speed(20.0f),
        jumpForce(10.0f),
        mouseSensitivity(0.5),
        input(std::move(input)),
        window(std::move(window))
    {
        windowResizeHandle = this->window->onWindowResize.subscribe(
            [this](const WindowResizeEvent& e) {
                camera.createProjection(static_cast<float>(e.width),
                    static_cast<float>(e.height));
            }
        );
    }

    CameraController::~CameraController()
    {
        window->onWindowResize.unsubcribe(windowResizeHandle);
    }

    const Camera& CameraController::getCamera() const
    {
        return camera;
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
            glm::quat yaw = glm::angleAxis(glm::radians(deltaX), glm::dvec3(0.0, 1.0, 0.0));
            glm::quat pitch = glm::angleAxis(glm::radians(deltaY), glm::dvec3(1.0, 0.0, 0.0));
            glm::quat q = glm::normalize(pitch * camera.transform.rotation * yaw);
            camera.transform.rotation = glm::normalize(q);
        }

        camera.update(deltaTime);
    }
}