#include "TextureArray.hpp"
#include "Core/Logger.hpp"
namespace GameEngine
{
    TextureArray::TextureArray(int width, int height, const std::unordered_map<std::string, ImageData>& textures) :
        texture(TextureTarget::Texture2DArray), textureWidth(width), textureHeight(height), texturesCount(textures.size())
    {
        texture.bind();
        texture.setWrapS(WrapMode::Repeat);
        texture.setWrapT(WrapMode::Repeat);
        texture.setMinFilter(MinFilter::Linear);
        texture.setMagFilter(MagFilter::Linear);
        glTexStorage3D(
            static_cast<GLenum>(TextureTarget::Texture2DArray), 
            1, 
            GL_RGBA8, 
            static_cast<GLsizei>(width), 
            static_cast<GLsizei>(height),
            static_cast<GLsizei>(texturesCount)
        );
        int index = 0;
        for (const auto& [name, imageData] : textures)
        {
            glTexSubImage3D(
                static_cast<GLenum>(TextureTarget::Texture2DArray), 
                0, 
                0, 
                0, 
                index, 
                textureWidth,
                textureHeight, 
                1,
                GL_RGBA, 
                GL_UNSIGNED_BYTE, 
                imageData.get()
            );
            namesToLayers[name] = index;
            index++;
        }

        texture.GenerateMipmap();
    }


    void TextureArray::setLayer(const std::string& name, int index, ImageData imageData)
    {
        if (index >= texturesCount)
        {
            LOG_ERROR("Texture index is out of bounds");
            return;
        }
        glTexSubImage3D(static_cast<GLenum>(TextureTarget::Texture2DArray), 0, 0, 0, index, textureWidth, textureHeight, 1, GL_BGR, GL_UNSIGNED_BYTE, imageData.get());
        namesToLayers[name] = index;
    }

    int TextureArray::getLayerIndex(const std::string& name) const
    {
        auto it = namesToLayers.find(name);
        if (it == namesToLayers.end())
        {
            LOG_ERROR("Texture name is not found");
            throw std::runtime_error("Texture name not found in array");
        }
        return it->second;
    }
}