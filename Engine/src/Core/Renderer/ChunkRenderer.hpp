#pragma once
#include "Core/World/World.hpp"
#include "Core/World/Chunk.hpp"
#include "Core/Graphics/Shaders/Shader.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Graphics/Meshing/ChunkMesh.hpp"
#include "Core/Graphics/Textures/TextureArray.hpp"

namespace GameEngine
{

    void renderChunk(const Shader& shader, const Chunk& chunk, const ChunkMesh& chunkMesh, const Camera& camera, const TextureArray& textureArray);

    void renderWorld(const Shader& shader, const World& world, const Camera& camera, const TextureArray& textureArray);
}