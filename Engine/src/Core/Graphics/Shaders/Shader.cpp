#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Engine/Core/Graphics/Shaders/Shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Engine/Core/Logger.hpp"

namespace Engine
{
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        compile(vertexSource, fragmentSource);
    };
    Shader::~Shader() {
        glDeleteProgram(shaderProgram);
    };

    void Shader::use() const
    {
        glUseProgram(shaderProgram);
    }
    void Shader::compile(const std::string& vertexSource, const std::string& fragmentSource)
    {
        // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexSourcePtr = vertexSource.c_str();

        glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            LOG_ERROR("Shader vertex compilation failed: {}", infoLog);
        }

        // fragment shader
        const char* fragmentSourcePtr = fragmentSource.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            LOG_ERROR("Shader fragment compilation failed: {}", infoLog);
        }

        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            LOG_ERROR("Shader program linking failed:\n{}", infoLog);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    GLint Shader::getLocation(const std::string& name) const
    {
        return glGetUniformLocation(shaderProgram, name.c_str());
    }
    void Shader::setInt(const std::string &name, const int32_t value) const
    {
        glUniform1i(getLocation(name), value);
    }
    void Shader::setFloat(const std::string& name, const float_t value) const
    {
        glUniform1f(getLocation(name), value);
    }
    void Shader::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(getLocation(name), 1, &value[0]);
    }
    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(getLocation(name), 1, &value[0]);
    }
    void Shader::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(getLocation(name), 1, &value[0]);
    }
    void Shader::setMat2(const std::string& name, const glm::mat2& value) const
    {
        glUniformMatrix2fv(getLocation(name), 1, false, &value[0][0]);
    }
    void Shader::setMat3(const std::string& name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(getLocation(name), 1, false, &value[0][0]);
    }
    void Shader::setMat4(const std::string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(getLocation(name), 1, false, &value[0][0]);
    }
}