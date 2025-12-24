#include "Engine/Core/World/ChunkController.hpp"
#include "Engine/Core/World/Level.hpp"
#include "Engine/Core/World/LevelGenerator.hpp"
#include <memory>

namespace Engine
{
    ChunkController::ChunkController(std::shared_ptr<Level> level, std::unique_ptr<LevelGenerator> levelGenerator) :
        level(std::move(level)),
        levelGenerator(std::move(levelGenerator))
    { }

    void ChunkController::loadChunk(glm::ivec3 position)
    {

    }

    void ChunkController::unloadChunk(glm::ivec3 position)
    {

    }

    void ChunkController::update()
    {

    }

}