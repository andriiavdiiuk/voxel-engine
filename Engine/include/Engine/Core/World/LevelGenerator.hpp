#pragma once
#include "Chunk.hpp"
#include <vector>
#include "WorldDefinitions.hpp"
#include <memory>
namespace Engine
{
    struct Biome;

    struct LevelGeneratorParams
    {
        std::vector<std::shared_ptr<Biome>> biomes;
        size_t seed;
        int maxWorldHeight;
        int minWorldHeight;
    };

    class LevelGenerator
    {
    public:
        LevelGenerator(const LevelGeneratorParams& params);
        ~LevelGenerator() = default;
        void generate(glm::ivec3 position, Chunk& chunk);

    private:
        const LevelGeneratorParams params;

    };
}