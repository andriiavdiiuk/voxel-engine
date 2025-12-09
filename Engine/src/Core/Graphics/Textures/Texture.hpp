#pragma once
#include <glad/glad.h>
#include <stdint.h>
#include <string>
#include <stb/stb_image.h>
#include <memory>
#include "TextureParameters.hpp"

namespace GameEngine
{
    using ImageData = std::unique_ptr<stbi_uc, decltype(&stbi_image_free)>;

    class Texture
    {
    public:
        Texture(TextureTarget target);
        ~Texture();

        void bind(GLenum textureUnit) const;
        void bind() const;

        void setWrapS(WrapMode wrapMode);
        void setWrapT(WrapMode wrapMode);
        void setWrapR(WrapMode wrapMode);

        void setMinFilter(MinFilter minFilter);
        void setMagFilter(MagFilter magFilter);

        void setCompareMode(CompareMode compareMode);
        void setCompareFunc(CompareFunc compareFunc);
        void setDepthStencilMode(DepthStencilMode depthStencilMode);

        void setLodBias(GLfloat lodBias);
        void setBaseLevel(GLint baseLevel);
        void setMaxLevel(GLint maxLevel);

        void setMinLod(GLfloat minLod);
        void setMaxLod(GLfloat maxLod);

        void setSwizzleR(Swizzle swizzle);
        void setSwizzleG(Swizzle swizzle);
        void setSwizzleB(Swizzle swizzle);
        void setSwizzleA(Swizzle swizzle);
        void setSwizzleRGBA(Swizzle r, Swizzle g, Swizzle b, Swizzle a);
        void setBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

        void GenerateMipmap();

    protected:
        GLuint id;
        TextureTarget textureTarget;
    };
}