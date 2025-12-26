#include "Engine/Core/World/ChunkController.hpp"
#include "Engine/Core/World/Level.hpp"
#include "Engine/Core/World/LevelGenerator.hpp"
#include "Engine/Core/Resources/AssetStorage.hpp"
#include "Engine/Core/Resources/VoxelResource.hpp"
#include "Engine/Core/Graphics/Textures/TextureArray.hpp"
#include <memory>

namespace Engine
{
    static bool isPointInsideSphere(glm::ivec3 point, glm::ivec3 sphereCenter, float radius)
    {
        int dx = sphereCenter.x - point.x;
        int dy = sphereCenter.y - point.y;
        int dz = sphereCenter.z - point.z;

        return (dx * dx + dy * dy + dz * dz) <= radius * radius;
    }

    ChunkController::ChunkController(ChunkControllerParams params, std::unique_ptr<LevelGenerator> levelGenerator,
        std::shared_ptr<AssetStorage<VoxelResource>> voxelStorage, std::shared_ptr<AssetStorage<TextureArray>> textureArrayStorage) :
        params(params),
        levelGenerator(std::move(levelGenerator)),
        voxelStorage(std::move(voxelStorage)),
        textureArrayStorage(std::move(textureArrayStorage))
    {
    
    }

    void ChunkController::createChunk(Level& level, glm::ivec3 chunkPosition) const
    {
        if (level.chunks.contains(chunkPosition))
        {
            return;
        }
        Chunk& chunk = level.chunks.try_emplace(chunkPosition, chunkPosition).first->second;
        levelGenerator->generate(chunkPosition, chunk);
    }

    void ChunkController::createChunkMesh(Level& level, glm::ivec3 chunkPosition) const
    {
        auto chunkIt = level.chunks.find(chunkPosition);
        if (chunkIt != level.chunks.end())
        {
            Chunk& chunk = chunkIt->second;
            
            auto meshIt = level.chunkMeshes.find(chunkPosition);
            if (meshIt == level.chunkMeshes.end())
            {
                ChunkMesh& mesh = level.chunkMeshes.try_emplace(chunkPosition).first->second;

                mesh.generateFromChunk(chunk, voxelStorage, textureArrayStorage);
            }

        }

    }

    void ChunkController::update(Level& level, glm::ivec3 chunkPosition) const
    {
        int R = params.loadingDistance;
        for (int x = chunkPosition.x - R; x <= chunkPosition.x + R; ++x) {
            for (int y = chunkPosition.y - R; y <= chunkPosition.y + R; ++y) {
                for (int z = chunkPosition.z - R; z <= chunkPosition.z + R; ++z) {
                    glm::ivec3 pos(x, y, z);
                    if (isPointInsideSphere(pos, chunkPosition, params.loadingDistance)) {
                        createChunk(level, pos);
                    }
                    else {
                        level.chunks.erase(pos);
                    }

                    if (isPointInsideSphere(pos, chunkPosition, params.meshingDistance)) {
                        createChunkMesh(level, pos);
                    }
                    else {

                        level.chunkMeshes.erase(pos);
                    }
                }
            }
        }
    }
}