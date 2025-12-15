#pragma once
#include <vector>
#include "Voxel.hpp"
#include <string>

namespace Engine
{
    struct BiomeLayer
    {
        std::vector<AssetHandle> voxels;
        int thickness;
    };

    struct Biome
    {
        double weight;
        std::vector<BiomeLayer> layers;
    };
}