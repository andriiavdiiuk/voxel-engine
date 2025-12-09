#pragma once
#include <stdint.h>

namespace GameEngine
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
