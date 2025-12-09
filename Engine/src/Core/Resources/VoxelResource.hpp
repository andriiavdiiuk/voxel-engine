#pragma once
#include <unordered_map>
#include "AssetHandle.hpp"
namespace GameEngine
{
    enum class VoxelFace
    {
        Front,
        Back,
        Up,
        Down,
        Left,
        Right
    };

    struct VoxelResource
    {
        AssetHandle textureArray;
        std::unordered_map<VoxelFace, std::string> textures;
    };
}