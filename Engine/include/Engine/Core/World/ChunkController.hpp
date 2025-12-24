#pragma once
#include <memory>
#include <glm/glm.hpp>
namespace Engine
{
    class Level;
    class LevelGenerator;

    struct ChunkControllerParams
    {
        int loadingDistance;
    };

    class ChunkController
    {
    public:
        ChunkController(std::shared_ptr<Level> level, std::unique_ptr<LevelGenerator> levelGenerator);
        ~ChunkController() = default;

        void loadChunk(glm::ivec3 position);
        void unloadChunk(glm::ivec3 position);

        void update();

    private:
        std::shared_ptr<Level> level;
        std::unique_ptr<LevelGenerator> levelGenerator;
    };
}