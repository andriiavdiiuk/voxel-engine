#pragma once
#include "Core/World/Chunk.hpp"
#include "glm/glm.hpp"
#include <vector>
#include "WorldDefinitions.hpp"
#include <memory>
namespace GameEngine
{
    struct Biome;

    struct WorldGeneratorParams
    {
        std::vector<std::shared_ptr<Biome>> biomes;
        size_t seed;
    };

    class WorldGenerator
    {
    public:
        WorldGenerator(const WorldGeneratorParams& params);
        ~WorldGenerator() = default;
        void generate(glm::ivec3 position, Chunk& chunk);

    private:
        const WorldGeneratorParams params;

    };
}