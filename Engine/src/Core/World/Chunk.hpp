#pragma once
#include <vector>
#include "Voxel.hpp"
#include "VoxelStorage.hpp"
#include <glm/glm.hpp>
#include "Common/BitArray.hpp"

namespace GameEngine
{
    constexpr int CHUNK_SIZE = 16;
    class Chunk
    {
    public:
        Chunk(const glm::ivec3& chunkPosition);
        ~Chunk() = default;
        const Voxel& getVoxel(const glm::ivec3& position) const;
        void setVoxel(const glm::ivec3& position, const Voxel& voxel);
        glm::ivec3 getChunkPosition() const { return chunkPosition; };
        const std::vector<uint8_t>& getVoxelBuffer() const { return voxels.getData().getBuffer(); };

     private:
        glm::ivec3 chunkPosition;
        VoxelStorage voxels;
        int toIndex(const glm::ivec3& position) const;
    };
}