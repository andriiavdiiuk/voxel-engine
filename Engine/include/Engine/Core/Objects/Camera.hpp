#pragma once
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Core/Components/Transform.hpp"
#include <memory>
namespace Engine
{
    class Camera
    {
    public:
        float fov;
        float near;
        float far;

        Transform transform;

        Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, const glm::vec2& viewport);
        ~Camera();

        void lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
        void createProjection(float width, float height);

        const glm::mat4& getView() const;
        const glm::mat4& getProjection() const;
        const glm::vec3& getUp() const;
        const glm::vec3& getRight() const;
        const glm::vec3& getForward() const;

        virtual void update(double deltaTime);

    private:
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 forward;

        void calculateView();
        void calculateVectors();
    };
}