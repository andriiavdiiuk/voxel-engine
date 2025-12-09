#include "AssetLoaders.hpp"
#include <stb/stb_image.h>
#include <stdexcept>
#include "Core/Graphics/Textures/Texture2D.hpp"
#include "Core/Graphics/Textures/TextureArray.hpp"
#include "Core/Graphics/Shaders/Shader.hpp"
#include "Core/World/Voxel.hpp"
#include "Core/Logger.hpp"
#include <glaze/glaze.hpp>
#include "Utils/FileUtils.hpp"
#include "VoxelResource.hpp"


template <>
struct glz::meta<GameEngine::VoxelFace> {
    static constexpr auto value = glz::enumerate(
        "up", GameEngine::VoxelFace::Up,
        "down", GameEngine::VoxelFace::Down,
        "right", GameEngine::VoxelFace::Right,
        "left", GameEngine::VoxelFace::Left,
        "front", GameEngine::VoxelFace::Front,
        "back", GameEngine::VoxelFace::Back
    );
};

namespace GameEngine
{

    std::unique_ptr<std::unordered_map<std::string, std::string>> loadRegistry(const std::string& path)
    {
        std::unordered_map<std::string, std::string> data{};
        auto ec = glz::read_file_json(data, path, std::string{});
        if (ec)
        {
            std::string desc = glz::format_error(ec, std::string{});
            std::string msg = std::format("Failed to load registry '{}': {}", path, desc);
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
        }
        return std::make_unique<std::unordered_map<std::string, std::string>>(data);
    }


    std::shared_ptr<Texture2D> loadTexture2D(const std::string& path)
    {
        int width, height, nrChannels;

        ImageData data(stbi_load(path.c_str(), &width, &height, &nrChannels, 0), stbi_image_free);
        if (!data)
        {
            std::string desc = std::string(stbi_failure_reason());
            std::string msg = std::format("Failed to load texture '{}': {}", path, desc);
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
        }
        return std::make_shared<Texture2D>(width, height, std::move(data));
    }

    struct ShaderJson
    {
        std::string fragment_shader_path;
        std::string vertex_shader_path;
    };

    std::shared_ptr<Shader> loadShader(const std::string& path)
    {
        ShaderJson data{};
        auto ec = glz::read_file_json(data, path, std::string{});
        if (ec)
        {
            std::string desc = glz::format_error(ec, std::string{});
            std::string msg = std::format("Failed to load shader '{}': {}", path, desc);
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
        }
        return std::make_shared<Shader>(readFile(data.vertex_shader_path), readFile(data.fragment_shader_path));
    }

    struct TextureArrayJson
    {
        std::string name;
        std::string path;
    };

    std::shared_ptr<TextureArray> loadTextureArray(const std::string& path)
    {
        std::vector<TextureArrayJson> data{};
        auto ec = glz::read_file_json(data, path, std::string{});
        if (ec)
        {
            std::string desc = glz::format_error(ec, std::string{});
            std::string msg = std::format("Failed to load texture array '{}': {}", path, desc);
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
        }

        std::unordered_map<std::string, ImageData> textures;

        int maxWidth = 0, maxHeight = 0;
        int width = 0, height = 0, nrChannels = 0;
        for (const auto& texture : data)
        {
            ImageData image(stbi_load(texture.path.c_str(), &width, &height, &nrChannels, 4), stbi_image_free);
            if (!image)
            {
                std::string desc = std::string(stbi_failure_reason());
                std::string msg = std::format("Failed to load texture '{}': {}", path, desc);
                LOG_ERROR(msg);
                throw std::runtime_error(msg);
            }
            textures.emplace(texture.name, std::move(image));

            if (width > maxWidth) { maxWidth = width; };
            if (height > maxHeight) { maxHeight = height; };
        }
        return std::make_shared<TextureArray>(maxWidth, maxHeight, textures);
    }

    struct VoxelResourceJson
    {
        std::string textureArray;
        std::unordered_map<VoxelFace, std::string> textures;
    };

    std::shared_ptr<VoxelResource> loadVoxel(const std::string& path)
    {
        VoxelResourceJson data{};
        auto ec = glz::read_file_json(data, path, std::string{});
        if (ec)
        {
            std::string desc = glz::format_error(ec, std::string{});
            std::string msg = std::format("Failed to load voxel '{}': {}", path, desc);
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
            
        }
        VoxelResource resource = VoxelResource();
        resource.textureArray = AssetHandle::fromString(data.textureArray);
        resource.textures = data.textures;
        return std::make_shared<VoxelResource>(resource);
    }
  
}
