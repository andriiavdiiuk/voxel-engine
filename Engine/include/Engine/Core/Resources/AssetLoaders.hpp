#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace Engine
{
				class Texture2D;
				class Shader;
				class TextureArray;
				struct VoxelResource;
				struct Biome;

				std::shared_ptr<Texture2D> loadTexture2D(const std::string& path);

				std::shared_ptr<Shader> loadShader(const std::string& path);

				std::shared_ptr<TextureArray> loadTextureArray(const std::string& path);

				std::shared_ptr<VoxelResource> loadVoxel(const std::string& path);

				std::shared_ptr<Biome> loadBiome(const std::string& path);

				std::unique_ptr<std::unordered_map<std::string, std::string>> loadRegistry(const std::string& path);
}