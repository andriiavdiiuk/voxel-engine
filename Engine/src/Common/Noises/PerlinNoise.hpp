#pragma once
#include <vector>
namespace GameEngine
{
    double perlinNoise2D(double x, double y, size_t seed);
    double perlinNoiseOctave2D(double x, double y, size_t seed, int octaves, int gridSize, double contrast);
    std::vector<std::vector<double>> perlinNoise2D(int width, int height, int startX, int startY, int octaves, int gridSize, double contrast, size_t seed);
}