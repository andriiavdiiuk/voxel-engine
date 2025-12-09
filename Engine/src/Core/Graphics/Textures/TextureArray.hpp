#pragma once
#include <glad/glad.h>
#include <memory>
#include <stb/stb_image.h>
#include "Texture.hpp"
#include <unordered_map>
namespace GameEngine
{

    class TextureArray
    {
    public:
        TextureArray(int width, int height, const std::unordered_map<std::string, ImageData>& textures);
        ~TextureArray() = default;

        void setLayer(const std::string& name, int index, ImageData imageData);
        int getLayerIndex(const std::string& name) const;
        void bind(GLenum textureUnit) const  { texture.bind(textureUnit); };
        void bind() const  { texture.bind(); };
        int getTextureWidth() const { return textureWidth; }
        int getTextureHeight() const { return textureHeight; }
        int getTexturesCount() const { return texturesCount; }
        Texture getTextureHandle() const { return texture; };

    private:
        Texture texture;
        int textureWidth;
        int textureHeight;
        int texturesCount;
        std::unordered_map<std::string, int> namesToLayers;
    };
}