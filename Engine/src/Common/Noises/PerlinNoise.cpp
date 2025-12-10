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

static Coords randomGradient2D(int ix, int iy)
{
    constexpr int w = 8 * sizeof(int);
    constexpr int s = w / 2; // rotation width
    unsigned a = static_cast<unsigned>(ix);
    unsigned b = static_cast<unsigned>(iy);
    a *= 3284157443; b ^= a << s | a >> w - s;
    b *= 1911520717; a ^= b << s | b >> w - s;
    a *= 2048419325;
    double random = static_cast<double>(a) * (3.14159265 / static_cast<double>(~(~0u >> 1))); // in [0, 2*Pi]
    Coords v{ 
        .x = std::cos(random), 
        .y = std::sin(random) 
    };
    return v;
}

static double dotGridGradient2D(int ix, int iy, double x, double y)
{
    Coords grad = randomGradient2D(ix, iy);

    // Compute the distance vector
    double dx = x - ix;
    double dy = y - iy;

    // Compute the dot-product
    return dx * grad.x + dy * grad.y;

}

namespace GameEngine
{
    double perlinNoise2D(double x, double y)
    {
        int x0 = static_cast<int>(x);
        int y0 = static_cast<int>(y);
        int x1 = x0 + 1;
        int y1 = y0 + 1;

        // interpolation weights
        double sx = x - x0;
        double sy = y - y0;

        // Compute and interpolate top two corners
        double n0 = dotGridGradient2D(x0, y0, x, y);
        double n1 = dotGridGradient2D(x1, y0, x, y);
        double ix0 = interpolate2D(n0, n1, sx);

        // Compute and interpolate bottom two corners
        n0 = dotGridGradient2D(x0, y1, x, y);
        n1 = dotGridGradient2D(x1, y1, x, y);
        double ix1 = interpolate2D(n0, n1, sx);

        // Final step: interpolate between the two previously interpolated values, now in y
        double value = interpolate2D(ix0, ix1, sy);

        return value;
    }

    double perlinNoiseOctave2D(double x, double y, int octaves, int gridSize, double contrast)
    {
        double frequency = 1;
        double amplitude = 1;
        double value = 0;
        for (int i = 0; i < octaves; i++)
        {
            value += perlinNoise2D(x * frequency / gridSize, y * frequency / gridSize) * amplitude;

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

    std::vector<std::vector<double>> perlinNoise2D(int width, int height, int startX, int startY, int octaves, int gridSize, double contrast)
    {
        std::vector<std::vector<double>> noise(height, std::vector<double>(width, 0.0));

        for (int i = 0; i < width; ++i)       
        {
            for (int j = 0; j < height; ++j)  
            {
                double x = startX + i;
                double y = startY + j;

                double val = perlinNoiseOctave2D(x, y, octaves, gridSize, contrast);

                noise[i][j] = val; 
            }
        }

        return noise;
    }
}