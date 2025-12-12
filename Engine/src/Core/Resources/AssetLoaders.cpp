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
#include "AssetHandle.hpp"

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


template <>
struct glz::meta<GameEngine::VoxelResource>
{
    using T = GameEngine::VoxelResource;

    static constexpr auto read_textures = [](T& voxel, std::string const& input, glz::context& ctx) {
        voxel.textureArray = GameEngine::AssetHandle::fromString(input);
    };

    static constexpr auto value = glz::object(
        "textureArray", glz::custom<read_textures, &T::textureArray>,
        "textures", &T::textures
    );
};


template <typename T>
void loadJson(T& out, const std::string& path, const std::string& descName)
{
    auto ec = glz::read_file_json(out, path, std::string{});
    if (ec)
    {
        std::string desc = glz::format_error(ec, std::string{});
        std::string msg = std::format("Failed to load {} '{}': {}", descName, path, desc);
        LOG_ERROR(msg);
        throw std::runtime_error(msg);
    }
}


namespace GameEngine
{

    ImageData loadImageData(const std::string& path, int& width, int& height, int& nrChannels, int desired_channels)
    {
        ImageData data(stbi_load(path.c_str(), &width, &height, &nrChannels, desired_channels), stbi_image_free);
        if (!data)
        {
            std::string msg = std::format("Failed to load texture '{}': {}", path, stbi_failure_reason());
            LOG_ERROR(msg);
            throw std::runtime_error(msg);
        }
        return data;
    }


    std::unique_ptr<std::unordered_map<std::string, std::string>> loadRegistry(const std::string& path)
    {
        std::unordered_map<std::string, std::string> data{};
        loadJson<std::unordered_map<std::string, std::string>>(data, path, "registry");
        return std::make_unique<std::unordered_map<std::string, std::string>>(data);
    }


    std::shared_ptr<Texture2D> loadTexture2D(const std::string& path)
    {
        int width, height, nrChannels;
        auto data = loadImageData(path, width, height, nrChannels, 0);
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
        loadJson<ShaderJson>(data, path, "shader");
        return std::make_shared<Shader>(readFile(data.vertex_shader_path), readFile(data.fragment_shader_path));
    }


    struct TextureArrayJson
    {
        std::string name;
        std::string path;
    };

    std::shared_ptr<TextureArray> loadTextureArray(const std::string& path)
    {
        std::vector<TextureArrayJson> data;
        loadJson<std::vector<TextureArrayJson>>(data, path, "texture array");

        std::unordered_map<std::string, ImageData> textures;

        int maxWidth = 0, maxHeight = 0;
        int width = 0, height = 0, nrChannels = 0;
        for (const auto& texture : data)
        {
            ImageData image = loadImageData(texture.path, width, height, nrChannels, 4);
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
        VoxelResource data{};
        loadJson<VoxelResource>(data, path, "voxel");
        return std::make_shared<VoxelResource>(data);
    }
}
