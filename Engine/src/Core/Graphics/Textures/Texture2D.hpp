#pragma once
#include <glad/glad.h>
#include <stdint.h>
#include <string>
#include <stb/stb_image.h>
#include <memory>
#include "Texture.hpp"

namespace GameEngine
{
    using ImageData = std::unique_ptr<stbi_uc, decltype(&stbi_image_free)>;

    class Texture2D
    {
    public:
        Texture2D(int width, int height, ImageData data);
        ~Texture2D() = default;
        
        void bind(GLenum textureUnit) { texture.bind(textureUnit); };
        void bind() { texture.bind(); };
        Texture getTextureHandle() const { return texture; };
        int getWidth() const { return width; };
        int getHeight() const { return height; };


    private:
        Texture texture;
        int width;
        int height;
    };
}