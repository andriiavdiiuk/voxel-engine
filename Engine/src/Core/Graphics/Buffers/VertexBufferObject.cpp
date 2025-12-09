#include <glad/glad.h>
#include "VertexBufferObject.hpp";

namespace GameEngine
{
    VertexBufferObject::VertexBufferObject()
    {
        glGenBuffers(1, &id);
    }

    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &id);
    }

    void VertexBufferObject::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }
    void VertexBufferObject::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}