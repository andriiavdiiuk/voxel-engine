#pragma once
#include <vector>
#include "Core/Graphics/Buffers/IndexBufferObject.hpp"
#include "Core/Graphics/Buffers/VertexArrayObject.hpp"
#include "Core/Graphics/Buffers/VertexBufferObject.hpp"
#include "memory"
namespace GameEngine
{

    class Chunk;

    template<typename T>
    class AssetStorage;

    class VoxelResource;
    class TextureArray;

    class ChunkMesh
    {
    public:
        ChunkMesh() = default;
        ~ChunkMesh() = default;
        void generateFromChunk(const Chunk& chunk, std::shared_ptr<AssetStorage<VoxelResource>> voxelStorage, std::shared_ptr<AssetStorage<TextureArray>> textureArrayStorage);
        const std::vector<uint64_t>& getVertices() const { return vertices; }
        const std::vector<uint32_t>& getIndicies() const { return indices; }
        void bindVao() const { vao.bind(); };
        void unbindVao() const { vao.unbind(); };
    private:
        /**
         * One Vertex uses 64 bits;
         * Memory Layout: TTTTTTTT TTTTTTTT TTTTTTTT TTTTTTTT 0000 0000 0000 UU FFF ZZZZZ YYYYY XXXXX
         * X - x coordinate, 5 bits
         * Y - y coordinate, 5 bits
         * Z - z coordinate, 5 bits
         * F - face id, 3 bits
         * U - UV id, 2 bits
         * T - texture id, 32 bits
        */ 
        std::vector<uint64_t> vertices;
        std::vector<uint32_t> indices;
        VertexBufferObject vbo;
        IndexBufferObject ebo;
        VertexArrayObject vao;
        uint64_t packVertex(uint8_t x, uint8_t y, uint8_t z,uint8_t uv, uint8_t face, uint32_t texture);
        void addFace(uint8_t x, uint8_t y, uint8_t z, uint8_t face, uint32_t texture);
    };
}