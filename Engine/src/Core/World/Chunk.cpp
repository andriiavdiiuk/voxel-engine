#include "Chunk.hpp"

namespace GameEngine
{
    Chunk::Chunk(const glm::ivec3& chunkPosition)
        : voxels(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE), chunkPosition(chunkPosition)
    {
    }

    const Voxel& Chunk::getVoxel(const glm::ivec3& position) const
    {
        return voxels.getVoxel(toIndex(position));
    }

    void Chunk::setVoxel(const glm::ivec3& position, const Voxel& voxel)
    {
        voxels.setVoxel(toIndex(position), voxel);
    }

    int Chunk::toIndex(const glm::ivec3& position) const
    {
        return position.x + CHUNK_SIZE * (position.y + CHUNK_SIZE * position.z);
    }
}