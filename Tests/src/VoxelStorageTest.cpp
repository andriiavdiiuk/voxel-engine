#include <gtest/gtest.h>
#include <Engine/Core/World/VoxelStorage.hpp>
#include <Engine/Core/World/Voxel.hpp>

constexpr int chunkBlocks = 16 * 16 * 16;

TEST(VoxelStorageTest, SingleVoxelType) {
    Engine::VoxelStorage storage(chunkBlocks);
    Engine::Voxel voxel{ 1 };

    for (size_t i = 0; i < chunkBlocks; i++) {
        storage.setVoxel(i, voxel);
    }

    for (size_t i = 0; i < chunkBlocks; i++) {
        EXPECT_EQ(storage.getVoxel(i), voxel);
    }

}

TEST(VoxelStorageTest, FewVoxelTypes) {
    Engine::VoxelStorage storage(chunkBlocks);
    std::vector<Engine::Voxel> types = { {1}, {2}, {3}, {4} };

    for (size_t i = 0; i < chunkBlocks; i++) {
        storage.setVoxel(i, types[i % types.size()]);
    }

    for (size_t i = 0; i < chunkBlocks; i++) {
        auto v = storage.getVoxel(i);
        EXPECT_EQ(v, types[i % types.size()]);
    }
}

TEST(VoxelStorageTest, UniqueVoxelTypes) {
    Engine::VoxelStorage storage(4096);

    for (size_t i = 0; i < chunkBlocks; i++) {
        storage.setVoxel(i, Engine::Voxel{i});
    }

    for (size_t i = 0; i < chunkBlocks; i++) {
        EXPECT_EQ(storage.getVoxel(i), Engine::Voxel{ i });
    }
}

TEST(VoxelStorageTest, AccessUnsetVoxelReturnsEmptyVoxel) {
    Engine::VoxelStorage storage(chunkBlocks);

    Engine::Voxel airVoxel{ 0 };  // empty voxel

    for (size_t i = 0; i < chunkBlocks; ++i) {
        EXPECT_EQ(storage.getVoxel(i), airVoxel);
    }
}

TEST(VoxelStorageTest, FitData) {
    Engine::VoxelStorage storage(chunkBlocks);

    for (size_t i = 0; i < chunkBlocks; ++i) {
        storage.setVoxel(i, Engine::Voxel{ i % 32 });
    }

    EXPECT_EQ(storage.getPaletteSize(), 32);
    EXPECT_EQ(storage.getIndicesLength(), 5);

    for (size_t i = 0; i < chunkBlocks; ++i) {
        storage.setVoxel(i, Engine::Voxel{ i%5 });
    }

    storage.fitData();

    EXPECT_EQ(storage.getPaletteSize(), 5);
    EXPECT_EQ(storage.getIndicesLength(), 3);

    for (size_t i = 0; i < chunkBlocks; ++i) {
        EXPECT_EQ(storage.getVoxel(i), Engine::Voxel{ i%5 });
    }
}