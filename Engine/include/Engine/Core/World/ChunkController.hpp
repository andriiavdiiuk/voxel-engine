#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Level.hpp"
namespace Engine
{
    //class Level;
    class LevelGenerator;

    template<typename T>
    class AssetStorage;
    struct VoxelResource;
    class TextureArray;

    struct ChunkControllerParams
    {
        int loadingDistance;
        int meshingDistance;
    };

    class ChunkController
    {
    public:
        ChunkController(ChunkControllerParams params, std::unique_ptr<LevelGenerator> levelGenerator, 
            std::shared_ptr<AssetStorage<VoxelResource>> voxelStorage, std::shared_ptr<AssetStorage<TextureArray>> textureArrayStorage);

        ~ChunkController() = default;

        void update(Level& level, glm::ivec3 chunkPosition) const;

    private:
        ChunkControllerParams params;
        std::unique_ptr<LevelGenerator> levelGenerator;
        std::shared_ptr<AssetStorage<VoxelResource>> voxelStorage;
        std::shared_ptr<AssetStorage<TextureArray>> textureArrayStorage;

        void createChunk(Level& level, glm::ivec3 chunkPosition) const;
        void createChunkMesh(Level& level, glm::ivec3 chunkPosition) const;
    };
}