#include "Engine/Core/Objects/Camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "Engine/Core/Logger.hpp"
namespace Engine
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::vec2& viewport)
        : fov(90), near(0.1f), far(100), forward(glm::vec3(0.0f))
    {
        this->forward = front;
        this->up = up;
        this->transform.position = position;

        lookAt(position, position + front, up);
        createProjection(viewport.x, viewport.y);
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
        right = glm::conjugate(transform.rotation) * glm::vec3(1.0, 0.0, 0.0);
        up = glm::conjugate(transform.rotation) * glm::vec3(0.0, 1.0, 0.0);
        forward = glm::conjugate(transform.rotation) * glm::vec3(0.0, 0.0, -1.0);
    }

    void Camera::update(double deltaTime)
    {
        calculateVectors();
        calculateView();
    }
}

