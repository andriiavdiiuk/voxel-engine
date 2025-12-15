#include "Engine/Core/Renderer/ChunkRenderer.hpp"
#include <glad.h>
namespace Engine
{
    void renderChunk(const Shader& shader, const Chunk& chunk, const ChunkMesh& chunkMesh, const Camera& camera, const TextureArray& textureArray)
    {
        shader.use();
        shader.setMat4("view", camera.getView());
        shader.setMat4("projection", camera.getProjection());
        shader.setVec3("chunkPosition", chunk.getChunkPosition());
        shader.setInt("chunkSize", CHUNK_SIZE);
    
        textureArray.bind(GL_TEXTURE0);
        shader.setInt("texture0", 0);

        chunkMesh.bindVao();

        glDrawElements(GL_TRIANGLES, chunkMesh.getIndicies().size(), GL_UNSIGNED_INT, 0);

        chunkMesh.unbindVao();
    }
    
    void renderWorld(const Shader& shader, const World& world, const Camera& camera, const TextureArray& textureArray)
    {
        for (auto& [pos, chunk] : world.chunks)
        {
            auto it = world.chunkMeshes.find(pos);
            if (it != world.chunkMeshes.end())
            {
                const ChunkMesh& mesh = it->second;
                
                renderChunk(shader, chunk, mesh, camera, textureArray);
            }
        }
    }
}