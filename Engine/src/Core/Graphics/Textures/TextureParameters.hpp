#pragma once
#include <glad.h>
#include <optional>

namespace GameEngine
{
    enum class WrapMode : GLint
    {
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        Repeat = GL_REPEAT,
        MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
    };

    enum class MinFilter : GLint
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
    };

    enum class MagFilter : GLint
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR
    };

    enum class CompareMode : GLint
    {
        None = GL_NONE,
        CompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE
    };

    enum class CompareFunc : GLint
    {
        Lequal = GL_LEQUAL,
        Gequal = GL_GEQUAL,
        Less = GL_LESS,
        Greater = GL_GREATER,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Always = GL_ALWAYS,
        Never = GL_NEVER
    };

    enum class DepthStencilMode : GLint
    {
        DepthComponent = GL_DEPTH_COMPONENT,
        StencilIndex = GL_STENCIL_INDEX
    };

    enum class Swizzle : GLint
    {
        Red = GL_RED,
        Green = GL_GREEN,
        Blue = GL_BLUE,
        Alpha = GL_ALPHA,
        Zero = GL_ZERO,
        One = GL_ONE
    };

    enum class TextureTarget : GLenum
    {
        Texture1D = GL_TEXTURE_1D,
        Texture2D = GL_TEXTURE_2D,
        Texture3D = GL_TEXTURE_3D,
        TextureRectangle = GL_TEXTURE_RECTANGLE,
        TextureBuffer = GL_TEXTURE_BUFFER,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP,
        Texture1DArray = GL_TEXTURE_1D_ARRAY,
        Texture2DArray = GL_TEXTURE_2D_ARRAY,
        TextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
        Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };
}