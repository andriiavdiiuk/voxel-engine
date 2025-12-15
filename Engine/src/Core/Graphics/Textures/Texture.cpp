#include "Engine/Core/Graphics/Textures/Texture.hpp"
namespace Engine
{
    Texture::Texture(TextureTarget textureTarget) : textureTarget(textureTarget)
    {
        glGenTextures(1, &id);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    void Texture::bind(GLenum textureUnit) const
    {
        glActiveTexture(textureUnit);
        glBindTexture(static_cast<GLenum>(textureTarget), id);
    }

    void Texture::bind() const
    {
        glBindTexture(static_cast<GLenum>(textureTarget), id);
    }

    void Texture::setWrapS(WrapMode wrapMode)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapMode));
    }

    void Texture::setWrapT(WrapMode wrapMode)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapMode));
    }

    void Texture::setWrapR(WrapMode wrapMode)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_WRAP_R, static_cast<GLint>(wrapMode));
    }

    void Texture::setMinFilter(MinFilter minFilter)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
    }

    void Texture::setMagFilter(MagFilter magFilter)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
    }

    void Texture::setCompareMode(CompareMode compareMode)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(compareMode));
    }

    void Texture::setCompareFunc(CompareFunc compareFunc)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(compareFunc));
    }

    void Texture::setDepthStencilMode(DepthStencilMode depthStencilMode)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLint>(depthStencilMode));
    }

    void Texture::setLodBias(GLfloat lodBias)
    {
        glTexParameterf(static_cast<GLenum>(textureTarget), GL_TEXTURE_LOD_BIAS, lodBias);
    }

    void Texture::setBaseLevel(GLint baseLevel)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_BASE_LEVEL, baseLevel);
    }

    void Texture::setMaxLevel(GLint maxLevel)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_MAX_LEVEL, maxLevel);
    }

    void Texture::setMinLod(GLfloat minLod)
    {
        glTexParameterf(static_cast<GLenum>(textureTarget), GL_TEXTURE_MIN_LOD, minLod);
    }

    void Texture::setMaxLod(GLfloat maxLod)
    {
        glTexParameterf(static_cast<GLenum>(textureTarget), GL_TEXTURE_MAX_LOD, maxLod);
    }

    void Texture::setSwizzleR(Swizzle swizzle)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_SWIZZLE_R, static_cast<GLint>(swizzle));
    }

    void Texture::setSwizzleG(Swizzle swizzle)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_SWIZZLE_G, static_cast<GLint>(swizzle));
    }

    void Texture::setSwizzleB(Swizzle swizzle)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_SWIZZLE_B, static_cast<GLint>(swizzle));
    }

    void Texture::setSwizzleA(Swizzle swizzle)
    {
        glTexParameteri(static_cast<GLenum>(textureTarget), GL_TEXTURE_SWIZZLE_A, static_cast<GLint>(swizzle));
    }

    void Texture::setSwizzleRGBA(Swizzle r, Swizzle g, Swizzle b, Swizzle a)
    {
        GLint data[4] = { static_cast<GLint>(r), static_cast<GLint>(g),
                          static_cast<GLint>(b), static_cast<GLint>(a) };
        glTexParameteriv(static_cast<GLenum>(textureTarget), GL_TEXTURE_SWIZZLE_RGBA, data);
    }

    void Texture::setBorderColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        GLfloat data[4] = { r, g, b, a };
        glTexParameterfv(static_cast<GLenum>(textureTarget), GL_TEXTURE_BORDER_COLOR, data);
    }

    void Texture::GenerateMipmap()
    {
        glGenerateMipmap(static_cast<GLenum>(textureTarget));
        glGenerateTextureMipmap(id);
    }
}