#include "glad/glad.h"
#include "Engine/Core/Graphics/Buffers/VertexArrayObject.hpp"
#include "Engine/Core/Logger.hpp"
namespace Engine
{
    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &id);
    }
    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &id);
    }
    void VertexArrayObject::bind() const
    {
        glBindVertexArray(id);
    }
    void VertexArrayObject::unbind() const
    {
        glBindVertexArray(0);
    }
}