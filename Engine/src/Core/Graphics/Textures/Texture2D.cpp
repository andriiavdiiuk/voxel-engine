#include <glad/glad.h>
#include "Texture2D.hpp"
#include <stb/stb_image.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Core/Logger.hpp"

namespace GameEngine
{
    Texture2D::Texture2D(int width, int height, ImageData data)
        : texture(TextureTarget::Texture2D)
    {
        texture.bind();
        texture.setWrapS(WrapMode::Repeat);
        texture.setWrapT(WrapMode::Repeat);
        texture.setMinFilter(MinFilter::Linear);
        texture.setMagFilter(MagFilter::Linear);
        glTexImage2D(GL_TEXTURE_2D, 0, 0, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data.get());
    }
}