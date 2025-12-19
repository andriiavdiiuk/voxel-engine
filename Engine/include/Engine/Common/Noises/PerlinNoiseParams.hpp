#pragma once
namespace Engine
{
    struct PerlinNoiseParams
    {
        int octaves;
        int gridSize;
        double contrast;
    };

    struct PerlinNoiseGridParams
    {
        int width;
        int height;
        int startX;
        int startY;
        PerlinNoiseParams noise;
    };
}