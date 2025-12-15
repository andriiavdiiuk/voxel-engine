#include "Engine/Core/Graphics/Meshing/ChunkMesh.hpp"
#include <glm/glm.hpp>
#include <glad.h>
#include "Engine/Core/Logger.hpp"
#include "Engine/Core/World/Chunk.hpp"
#include "Engine/Core/Resources/AssetStorage.hpp"
#include "Engine/Core/Resources/VoxelResource.hpp"
#include "Engine/Core/Graphics/Textures/TextureArray.hpp"
namespace Engine
{
    constexpr uint8_t cubeUV[] =
    {
        // Front face
        0b01,
        0b11,
        0b10,
        0b00,

        // Back face 
        0b01,
        0b00,
        0b10,
        0b11,

        // Top face
        0b01,
        0b11,
        0b10,
        0b00,

        // Bottom face
        0b00,
        0b10,
        0b11,
        0b01,

        // Right face 
        0b11,
        0b10,
        0b00,
        0b01,

        // Left face
        0b01,
        0b11,
        0b10,
        0b00
    };

    constexpr uint8_t cubeVertecies[] =
    {
        // Front face
        0, 0, 1, // 0 
        1, 0, 1, // 1 
        1, 1, 1, // 2 
        0, 1, 1, // 3 

        // Back face 
        0, 0, 0, // 4
        0, 1, 0, // 5 
        1, 1, 0, // 6 
        1, 0, 0, // 7 

        // Top face 
        0, 1, 1, // 8 
        1, 1, 1, // 9 
        1, 1, 0, // 10 
        0, 1, 0, // 11 

        // Bottom face 
        0, 0, 0, // 12 
        1, 0, 0, // 13 
        1, 0, 1, // 14 
        0, 0, 1, // 15 

        // Right face 
        1, 0, 0, // 16 
        1, 1, 0, // 17 
        1, 1, 1, // 18 
        1, 0, 1, // 19 

        // Left face 
        0, 0, 0, // 20 
        0, 0, 1, // 21 
        0, 1, 1, // 22 
        0, 1, 0  // 23
    };

    constexpr uint32_t cubeIndices[] = {
        // Front face
        0, 1, 3,
        1, 2, 3,

        // Back face
        5, 4, 7,
        5, 7, 6,

        // Top face
        8, 9, 11,
        9, 10, 11,

        // Bottom face 
        12, 13, 15,
        13, 14, 15,

        // Right face 
        16, 18, 19,
        16, 17, 18,

        // Left face 
        22, 21, 20,
        20, 23, 22

    };

    const uint16_t faceIndices[6] = { 0, 1, 2, 0, 2, 3 };

    constexpr VoxelFace voxelFaceMap[6] = {
        VoxelFace::Front,
        VoxelFace::Back,
        VoxelFace::Up,
        VoxelFace::Down,
        VoxelFace::Left,
        VoxelFace::Right
    };

    void ChunkMesh::generateFromChunk(const Chunk& chunk, std::shared_ptr<AssetStorage<VoxelResource>> voxelStorage, std::shared_ptr<AssetStorage<TextureArray>> textureArrayStorage)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                for (int z = 0; z < CHUNK_SIZE; z++) {
                    {
                        auto voxel = chunk.getVoxel(glm::ivec3(x, y, z));
                        if (voxel.type == 0) continue; // skip empty voxel

                        for (uint8_t face = 0; face < 6; face++) {
                            glm::ivec3 neighborPos = glm::ivec3(x, y, z);
                            switch (face) {
                            case 0: neighborPos.z += 1; break; 
                            case 1: neighborPos.z -= 1; break; 
                            case 2: neighborPos.y += 1; break; 
                            case 3: neighborPos.y -= 1; break; 
                            case 4: neighborPos.x += 1; break; 
                            case 5: neighborPos.x -= 1; break;
                            }

                            bool isFaceVisible = false;

                            if (neighborPos.x < 0 || neighborPos.x >= CHUNK_SIZE ||
                                neighborPos.y < 0 || neighborPos.y >= CHUNK_SIZE ||
                                neighborPos.z < 0 || neighborPos.z >= CHUNK_SIZE)
                            {
                                isFaceVisible = true;
                            }
                            else {
                                auto neighborVoxel = chunk.getVoxel(neighborPos);
                                if (neighborVoxel.type == 0) // neighbor empty
                                    isFaceVisible = true;
                            }

                            if (isFaceVisible) {
                                auto voxelResource = voxelStorage->getAsset(voxel.type);
                                auto textureArrayResource = textureArrayStorage->getAsset(voxelResource->textureArray);
                                auto faceEnum = voxelFaceMap[face];
                                auto textureId = textureArrayResource->getLayerIndex(voxelResource->textures[faceEnum]);
                                addFace(x, y, z, face, textureId);
                            }
                        }
                    }
                }
            }
        }
        vao.bind();
        vbo.bind();
        vbo.setBufferData<uint64_t>(vertices.data(), vertices.size());
        ebo.bind();
        ebo.setBufferData(indices.data(), indices.size());

        // packed vertex
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, sizeof(uint64_t), nullptr);


        vbo.unbind();
        vao.unbind();
        ebo.unbind();
    }
    void ChunkMesh::addFace(uint8_t x, uint8_t y, uint8_t z, uint8_t face, uint32_t texture)
    {

        size_t startVertex = vertices.size();
        for (int i = 0; i < 4; i++)
        {
            int baseIndex = face * 12 + i * 3;
            uint8_t vx = cubeVertecies[baseIndex + 0];
            uint8_t vy = cubeVertecies[baseIndex + 1];
            uint8_t vz = cubeVertecies[baseIndex + 2];

            uint8_t uv_index = cubeUV[face * 4 + i];

            vertices.push_back(packVertex(
                vx + x,
                vy + y,
                vz + z,
                uv_index,
                face,
                texture
            ));

            for (int i = 0; i < 6; i++)
            {
                indices.push_back(startVertex + faceIndices[i]);
            }
        }
    }


    uint64_t ChunkMesh::packVertex(uint8_t x, uint8_t y, uint8_t z, uint8_t uv, uint8_t face, uint32_t texture)
    {
        uint64_t xBits = x & 31;
        uint64_t yBits = (static_cast<uint64_t>(y) & 31) << 5;
        uint64_t zBits = (static_cast<uint64_t>(z) & 31) << 10;
        uint64_t faceBits = (static_cast<uint64_t>(face) & 7) << 15;
        uint64_t uvBits = (static_cast<uint64_t>(uv) & 3) << 18;

        // Texture ID occupies the top 32 bits (32–63)
        uint64_t textureBits = (static_cast<uint64_t>(texture) & 0xFFFFFFFF) << 32;
        return xBits | yBits | zBits | uvBits | faceBits | textureBits;
    }

}