#pragma once
#include <glad.h>
namespace GameEngine
{
    class IndexBufferObject
    {
    public:

        IndexBufferObject();
        ~IndexBufferObject();

        void bind() const;
        void unbind() const;
        template<typename T>
        void setBufferData(const T* indices, int count)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), indices, GL_STATIC_DRAW);
        }

    private:
        GLuint id;
    };
}

