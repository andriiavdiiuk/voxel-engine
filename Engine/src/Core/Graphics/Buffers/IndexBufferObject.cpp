#include <glad/glad.h>
#include "IndexBufferObject.hpp"

namespace GameEngine
{
    IndexBufferObject::IndexBufferObject()
    {
        glGenBuffers(1, &id);
    }

    IndexBufferObject::~IndexBufferObject()
    {
        glDeleteBuffers(1, &id);
    }

    void IndexBufferObject::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }
    void IndexBufferObject::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}