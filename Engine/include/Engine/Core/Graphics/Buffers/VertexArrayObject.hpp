#pragma once
#include <stdint.h>

namespace Engine
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject();
        ~VertexArrayObject();
        void bind() const;
        void unbind() const;

    private:
        GLuint id;
    };
}
