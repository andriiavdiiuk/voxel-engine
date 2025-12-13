#include "PerlinNoise.hpp"
#include <cmath>

struct Coords
{
    double x;
    double y;
};

static float interpolate2D(double a0, double a1, double w)
{
    /* // Clamping:
     * if (0.0 > w) return a0;
     * if (1.0 < w) return a1;
     */
    // Linear interpolation
    //return (a1 - a0) * w + a0;
    // Cubic interpolation, for a smooth appearance:
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;

    // An even smoother result with a second derivative equal to zero on boundaries:
    //return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

static Coords randomGradient2D(size_t ix, size_t iy, size_t seed)
{
    constexpr size_t w = 8 * sizeof(size_t);
    constexpr size_t s = w / 2; // rotation width

    size_t a = ix ^ (seed * 0xBF1BAFF8323E6C01ULL);
    size_t b = iy ^ (seed * 0xB5A291C5D6EF7741ULL);
    a *= 0xB61118FB40A1DE23ULL;
    b ^= a << s | a >> w - s;
    b *= 0xA8790BA45624BCADULL;
    a ^= b << s | b >> w - s;
    a *= 0xBB97E7B4DF0DF29BULL;
    double random = static_cast<double>(a) / static_cast<double>(0xFFFFFFFFFFFFFFFF) * 2.0 * 3.14159265; // in [0, 2*Pi]
    Coords v{ 
        .x = std::cos(random), 
        .y = std::sin(random) 
    };
    return v;
}

static double dotGridGradient2D(size_t ix, size_t iy, double x, double y, size_t seed)
{
    Coords grad = randomGradient2D(ix, iy, seed);

    // Compute the distance vector
    double dx = x - ix;
    double dy = y - iy;

    // Compute the dot-product
    return dx * grad.x + dy * grad.y;

}

namespace GameEngine
{
    double perlinNoise2D(double x, double y, size_t seed)
    {
        int x0 = static_cast<int>(x);
        int y0 = static_cast<int>(y);
        int x1 = x0 + 1;
        int y1 = y0 + 1;

        // interpolation weights
        double sx = x - x0;
        double sy = y - y0;

        // Compute and interpolate top two corners
        double n0 = dotGridGradient2D(x0, y0, x, y, seed);
        double n1 = dotGridGradient2D(x1, y0, x, y, seed);
        double ix0 = interpolate2D(n0, n1, sx);

        // Compute and interpolate bottom two corners
        n0 = dotGridGradient2D(x0, y1, x, y, seed);
        n1 = dotGridGradient2D(x1, y1, x, y, seed);
        double ix1 = interpolate2D(n0, n1, sx);

        // Final step: interpolate between the two previously interpolated values, now in y
        double value = interpolate2D(ix0, ix1, sy);

        return value;
    }

    double perlinNoiseOctave2D(double x, double y, size_t seed, int octaves, int gridSize, double contrast)
    {
        double frequency = 1;
        double amplitude = 1;
        double value = 0;
        for (int i = 0; i < octaves; i++)
        {
            value += perlinNoise2D(x * frequency / gridSize, y * frequency / gridSize, seed) * amplitude;

            amplitude /= 2;
            frequency *= 2;
        }
        value *= contrast;
        value = (value + 1) / 2;
        // Clipping
        if (value > 1.0f)
        {
            value = 1.0f;
        }
        else if (value < 0)
        {
            value = -0;
        }
        return value;
    }

    std::vector<std::vector<double>> perlinNoise2D(int width, int height, int startX, int startY, int octaves, int gridSize, double contrast, size_t seed)
    {
        std::vector<std::vector<double>> noise(height, std::vector<double>(width, 0.0));

        for (int i = 0; i < width; ++i)       
        {
            for (int j = 0; j < height; ++j)  
            {
                double x = startX + i;
                double y = startY + j;

                double val = perlinNoiseOctave2D(x, y, seed, octaves, gridSize, contrast);

                noise[i][j] = val; 
            }
        }

        return noise;
    }
}