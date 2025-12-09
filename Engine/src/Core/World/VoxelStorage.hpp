#pragma once
#include <vector>
#include "Voxel.hpp"
#include "Common/BitArray.hpp"

namespace GameEngine
{
    class VoxelStorage
    {
    public:
        VoxelStorage(size_t size);
        ~VoxelStorage() = default;
        void setVoxel(size_t index, const Voxel& voxel);
        const Voxel& getVoxel(size_t index) const;
        void fitData();
        const BitArray& getData() const { return data; };
        size_t getPaletteSize() const { return pallete.size(); }
        int getIndicesLength() const { return indicesLength; }

    private:

        struct PalleteEntry
        {
            size_t refcount = 0;
            Voxel voxel = Voxel{ 0 };
        };

        size_t size;
        int indicesLength;
        std::vector<PalleteEntry> pallete;

        BitArray data;

        void growData();
        size_t createNewPalleteEntry(const Voxel& voxel);
    };
}