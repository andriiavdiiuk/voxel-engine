#include "Camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "Core/Logger.hpp"
namespace GameEngine
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up)
        : fov(90), near(0.1f), far(100), forward(glm::vec3(0.0f))
    {
        this->forward = front;
        this->up = up;
        this->transform.position = position;

        lookAt(position, position + front, up);
        createProjection(1280, 768);
        //GameEngine::Engine::getWindow().onWindowResize.subscribe([camera = this](const GameEngine::WindowResizeEvent& e)
        //{
        //    camera->onWindowResize(e);
        //});
    }

    Camera::~Camera()
    {

    }

    const glm::mat4& Camera::getView() const
    {
        return view;
    }
    const glm::mat4& Camera::getProjection() const
    {
        return projection;
    }
    const glm::vec3& Camera::getUp() const
    {
        return up;
    }
    const glm::vec3& Camera::getRight() const
    {
        return right;
    }
    const glm::vec3& Camera::getForward() const
    {
        return forward;
    }

    void Camera::lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
    {
        view = glm::lookAt(position, target, up);
    }

    void Camera::createProjection(float width, float height)
    {
        projection = glm::perspective(fov, width / height, near, far);
    }

    void Camera::calculateView()
    {
        glm::mat4 rotate = glm::mat4_cast(transform.rotation);
        glm::mat4 translate = glm::mat4(1.0f);
        translate = glm::translate(translate, -transform.position);
        view = rotate * translate;
    }

    void Camera::calculateVectors()
    {
        right = glm::vec3(view[0][0], view[1][0], view[2][0]);
        up = glm::vec3(view[0][1], view[1][1], view[2][1]);
        forward = -glm::vec3(view[0][2], view[1][2], view[2][2]);
    }

    void Camera::rotate(double deltaX, double deltaY)
    {
        glm::quat pitch = glm::angleAxis(glm::radians(deltaY), glm::dvec3(1.0f, 0.0f, 0.0f));
        glm::quat yaw = glm::angleAxis(glm::radians(deltaX), glm::dvec3(0.0f, 1.0f, 0.0f));
        transform.rotation = glm::normalize(pitch * yaw * transform.rotation);
        calculateVectors();
        calculateView();
    }

    void Camera::onWindowResize(const WindowResizeEvent& event)
    {
        createProjection(event.width, event.height);
    }

    void Camera::update(double deltaTime)
    {
        calculateVectors();
        calculateView();
    }
}

