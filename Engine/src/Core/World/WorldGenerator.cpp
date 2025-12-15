#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "Engine/Core/World/WorldGenerator.hpp"
#include "Engine/Core/Resources/AssetHandle.hpp"
#include "Engine/Common/Noises/PerlinNoise.hpp"
#include <random>

namespace Engine
{
    static int random_weighted_index(const std::vector<double>& weights, size_t seed) {
        thread_local std::mt19937 gen(seed);
        std::discrete_distribution<> dist(weights.begin(), weights.end());
        return dist(gen);
    }

    static const AssetHandle& pickRandomVoxel(const std::vector<AssetHandle>& voxels, glm::ivec3 position)
    {
        thread_local std::mt19937 gen(std::hash<glm::ivec3>{}(position));
        std::uniform_int_distribution<> dist(0, static_cast<int>(voxels.size()) - 1);
        return voxels[dist(gen)];
    }

    static const std::shared_ptr<Biome> pickBiome(const std::vector<std::shared_ptr<Biome>>& biomes, glm::ivec3 position)
    {
        std::vector<double> weights;
        weights.reserve(biomes.size());

        for (const auto& b : biomes)
            weights.push_back(b->weight);
        size_t hash = std::hash<glm::ivec3>{}(position);
        int i = random_weighted_index(weights, hash);
        return biomes[i];
    }

  

    WorldGenerator::WorldGenerator(const WorldGeneratorParams& params) : params(params) {}

    void WorldGenerator::generate(glm::ivec3 position, Chunk& chunk)
    {
        constexpr double scale = 16.0;
        constexpr int octaves = 4;
        constexpr int gridSize = 64;
        constexpr double contrast = 1.0;

         std::shared_ptr<Biome> biome = pickBiome(params.biomes, position);

        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                double worldX = position.x * CHUNK_SIZE + x;
                double worldZ = position.z * CHUNK_SIZE + z;

                double height = perlinNoiseOctave2D(worldX, worldZ, params.seed, octaves, gridSize, contrast);
                int maxY = static_cast<int>(height * CHUNK_SIZE);
                
                int currentY = maxY;

                for (const auto& layer : biome->layers) {
                    for (int i = 0; i < layer.thickness && currentY >= 0; i++) {
                        auto voxel = pickRandomVoxel(layer.voxels, glm::ivec3{x,i,z});

                        chunk.setVoxel(glm::ivec3(x, currentY, z), Voxel{ voxel });

                        currentY--;
                    }
                }
            }
        }
    }

}