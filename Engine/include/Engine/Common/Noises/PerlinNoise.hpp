#pragma once
#include <vector>
#include "Engine/Common/Noises/PerlinNoiseParams.hpp"
namespace Engine
{
    double perlinNoise2D(double x, double y, size_t seed);
    double perlinNoiseOctave2D(double x, double y, size_t seed, const PerlinNoiseParams& params);
    std::vector<std::vector<double>> perlinNoise2D(const PerlinNoiseGridParams& params, size_t seed);
}