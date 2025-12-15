#include "Engine/Core/Input/Input.hpp"
#include "GameApplication.hpp"
#include <glm/glm.hpp>
#include "Engine/Core/Resources/AssetLoaders.hpp"
#include <string>
#include <random>
#include <memory>
#include "Engine/Core/Resources/DefaultAssets.hpp"
#include "Engine/Core/World/WorldGenerator.hpp"
#include <vector>
#include <string>
#include <iostream>

namespace Game
{
    GameApplication::GameApplication() :
        Application(),
        player(Engine::CameraController(input))
    {
        shaderStorage = std::make_shared<Engine::AssetStorage<Engine::Shader>>(
            *Engine::loadRegistry(std::string{ Engine::DefaultShaderRegistryPath }),
            Engine::loadShader
        );

        textureArrayStorage = std::make_shared<Engine::AssetStorage<Engine::TextureArray>>(
            *Engine::loadRegistry("./assets/registries/texture_array_registry.json"),
            Engine::loadTextureArray
        );

        voxelStorage = std::make_shared<Engine::AssetStorage<Engine::VoxelResource>>(
            *Engine::loadRegistry("./assets/registries/voxel_registry.json"),
            Engine::loadVoxel
        );

        biomeStorage = std::make_shared<Engine::AssetStorage<Engine::Biome>>(
            *Engine::loadRegistry("./assets/registries/biome_registry.json"),
            Engine::loadBiome
        );

        shaderStorage->loadAll();
        voxelStorage->loadAll();
        textureArrayStorage->loadAll();
        biomeStorage->loadAll();

        std::random_device rd;              
        std::mt19937_64 gen(rd());         
        std::uniform_int_distribution<size_t> dist(0, ~size_t(0));

        Engine::WorldGeneratorParams params;
        params.seed = dist(gen);
        params.biomes = std::vector{ biomeStorage->getAsset("plains") };
        Engine::WorldGenerator generator = Engine::WorldGenerator(params);

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                glm::ivec3 chunkPos(i, 0, j);
                Engine::Chunk& chunk = world.chunks.try_emplace(chunkPos, chunkPos).first->second;
                generator.generate(chunkPos, chunk);


                Engine::ChunkMesh& mesh = world.chunkMeshes.try_emplace(chunk.getChunkPosition()).first->second;
                mesh.generateFromChunk(chunk, voxelStorage, textureArrayStorage);
            }
        }
    }


    GameApplication::~GameApplication()
    {

    }


    void GameApplication::update(double deltaTime)
    {
        player.update(deltaTime);
    }

    void GameApplication::render(double deltaTime)
    {
        Engine::renderWorld(
            *shaderStorage->getAsset("voxel_shader"), 
            world,
            player.camera, 
            *textureArrayStorage->getAsset("textures"));
    }
}