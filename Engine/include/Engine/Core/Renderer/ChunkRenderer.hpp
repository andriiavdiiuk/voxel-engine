#pragma once
#include "Engine/Core/World/Level.hpp"
#include "Engine/Core/World/Chunk.hpp"
#include "Engine/Core/Graphics/Shaders/Shader.hpp"
#include "Engine/Core/Objects/Camera.hpp"
#include "Engine/Core/Graphics/Meshing/ChunkMesh.hpp"
#include "Engine/Core/Graphics/Textures/TextureArray.hpp"

namespace Engine
{

    void renderChunk(const Shader& shader, const Chunk& chunk, const ChunkMesh& chunkMesh, const Camera& camera, const TextureArray& textureArray);

    void renderLevel(const Shader& shader, const Level& world, const Camera& camera, const TextureArray& textureArray);
}