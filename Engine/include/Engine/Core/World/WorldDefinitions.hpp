#pragma once
#include <vector>
#include <string>
#include "Engine/Common/Noises/PerlinNoiseParams.hpp"

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
        PerlinNoiseParams noise;
    };
}