#include "glad/glad.h"
#include "VertexArrayObject.hpp"
#include "Core/Logger.hpp"
namespace GameEngine
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