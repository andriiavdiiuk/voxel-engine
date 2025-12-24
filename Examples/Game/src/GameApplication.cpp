#include "Engine/Core/Input/Input.hpp"
#include "GameApplication.hpp"
#include <glm/glm.hpp>
#include "Engine/Core/Resources/AssetLoaders.hpp"
#include <string>
#include <random>
#include <memory>
#include "Engine/Core/Resources/DefaultAssets.hpp"
#include "Engine/Core/World/LevelGenerator.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <Engine/Core/UI/ImGui/ImGuiDebugLayer.hpp>
namespace Game
{
    GameApplication::GameApplication() :
        Application(),
        player(Engine::CameraController(input, window)),
        enableDebug(false)
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

        Engine::LevelGeneratorParams params;
        params.seed = dist(gen);
        params.biomes = std::vector{ biomeStorage->getAsset("plains") };
        params.maxWorldHeight = 64;
        params.minWorldHeight = 0;
        Engine::LevelGenerator generator = Engine::LevelGenerator(params);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    glm::ivec3 chunkPos(i, j, k);
                    Engine::Chunk& chunk = world.chunks.try_emplace(chunkPos, chunkPos).first->second;
                    generator.generate(chunkPos, chunk);


                    Engine::ChunkMesh& mesh = world.chunkMeshes.try_emplace(chunk.getChunkPosition()).first->second;
                    mesh.generateFromChunk(chunk, voxelStorage, textureArrayStorage);
                }
            }
        }
    }


    GameApplication::~GameApplication()
    {

    }


    void GameApplication::update(double deltaTime)
    {
        if (input->getKeyboard().isKeyPressed(Engine::Key::GraveAccent))
        {
            enableDebug = !enableDebug;
        }

        Engine::CameraDebug(enableDebug, player.getCamera());


        player.update(deltaTime);
        
    }

    void GameApplication::render(double deltaTime)
    {
        Engine::renderLevel(
            *shaderStorage->getAsset("voxel_shader"), 
            world,
            player.getCamera(),
            *textureArrayStorage->getAsset("textures"));
    }
}