#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace GameEngine
{
    struct Transform
    {
        glm::vec3 position = glm::vec3();
        glm::quat rotation = glm::quat();
        glm::vec3 scale = glm::vec3(1.0f);
        inline glm::mat4 getModel() const {
            return glm::translate(glm::mat4(1.0f), scale) * glm::mat4_cast(rotation) * glm::translate(glm::mat4(1.0f), position);
        }
    };
}