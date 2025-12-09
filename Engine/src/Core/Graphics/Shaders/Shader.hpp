#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

namespace GameEngine
{
    class Shader {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void use() const;
        void setInt(const std::string& name, const int32_t value) const;
        void setFloat(const std::string& name, const float_t value) const;

        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;

        void setMat2(const std::string& name, const glm::mat2& value) const;
        void setMat3(const std::string& name, const glm::mat3& value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;

    private:
        GLuint shaderProgram;
        void compile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        GLint getLocation(const std::string& name) const;
    };
}
