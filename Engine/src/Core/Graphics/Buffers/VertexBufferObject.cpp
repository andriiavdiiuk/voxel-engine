#include <glad/glad.h>
#include "Engine/Core/Graphics/Buffers/VertexBufferObject.hpp";

namespace Engine
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