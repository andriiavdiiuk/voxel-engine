#pragma once
#include <Engine/Core/Application.hpp>
#include <Engine/Core/Graphics/Shaders/Shader.hpp>
#include <Engine/Core/Objects/CameraController.hpp>
#include <Engine/Core/Renderer/ChunkRenderer.hpp>
#include "Engine/Core/Graphics/Textures/Texture2D.hpp"
#include "Engine/Core/Graphics/Textures/TextureArray.hpp"
#include "Engine/Core/Resources/VoxelResource.hpp"
#include "Engine/Core/Resources/AssetStorage.hpp"
#include "Engine/Core/World/WorldDefinitions.hpp"
namespace Game
{
    class GameApplication : public Engine::Application
    {
    public:
        GameApplication();
        virtual ~GameApplication();
        virtual void update(double deltaTime) override;
        virtual void render(double deltaTime) override;

    private:
        bool isRunning;
        Engine::CameraController player;
        Engine::World world;
        std::shared_ptr<Engine::AssetStorage<Engine::TextureArray>> textureArrayStorage;
        std::shared_ptr<Engine::AssetStorage<Engine::Shader>> shaderStorage;
        std::shared_ptr<Engine::AssetStorage<Engine::VoxelResource>> voxelStorage;
        std::shared_ptr<Engine::AssetStorage<Engine::Biome>> biomeStorage;
    };
}