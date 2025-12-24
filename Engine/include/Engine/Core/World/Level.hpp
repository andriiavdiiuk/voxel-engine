#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <unordered_map>
#include "Chunk.hpp"
#include <glm/glm.hpp>
#include "Engine/Core/Graphics/Meshing/ChunkMesh.hpp"
namespace Engine
{
    class Level
    {
    public: 
        std::unordered_map<glm::ivec3, Chunk> chunks;
        std::unordered_map<glm::ivec3, ChunkMesh> chunkMeshes;
    };
}