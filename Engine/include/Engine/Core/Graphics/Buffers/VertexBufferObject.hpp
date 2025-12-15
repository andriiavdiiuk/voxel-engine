#pragma once
#include <stdint.h>
#include <glad.h>
namespace Engine
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        void bind() const;
        void unbind() const;

        template<typename T>
        void setBufferData(const T* data, int count)
        {
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
        }

    private:
        GLuint id;
    };
}

