#include "Engine/Core/World/VoxelStorage.hpp"
#include <unordered_map>
#include "Engine/Common/BitArray.hpp"
namespace Engine
{
    VoxelStorage::VoxelStorage(size_t size) : 
        indicesLength(1), 
        size(size),  
        data(size * indicesLength), 
        pallete(1, PalleteEntry{ size, Voxel{0} }) // index 0 is empty voxel with refcount = size
    { }

    void VoxelStorage::setVoxel(size_t index, const Voxel& voxel)
    {
        int paletteIndex = data.readBits(index * indicesLength, indicesLength);
        PalleteEntry& entry = pallete[paletteIndex];

        if (entry.refcount > 0)
            entry.refcount--;
        else
            entry.refcount = 0;

        auto it = std::find_if(pallete.begin(), pallete.end(), [&](const PalleteEntry& entry) {
            return entry.voxel == voxel;
            });

        // voxel already in pallete
        if (it != pallete.end())
        {
            paletteIndex = std::distance(pallete.begin(), it);
            data.writeBits(index * indicesLength, indicesLength, paletteIndex);
            pallete[paletteIndex].refcount++;
            return;
        }

        // can we overwrite the current palette entry?
        if (entry.refcount == 0)
        {
            entry.voxel = voxel;
            entry.refcount = 1;
            return;
        }

        // a new palette entry is needed
        paletteIndex = createNewPalleteEntry(voxel);
        data.writeBits(index * indicesLength, indicesLength, paletteIndex);
    }

    const Voxel& VoxelStorage::getVoxel(size_t index) const
    {
        int palleteIndex = data.readBits(index * indicesLength, indicesLength);
        return pallete[palleteIndex].voxel;
    }

    size_t VoxelStorage::createNewPalleteEntry(const Voxel& voxel)
    {
        // find first free (refcount == 0) palette entry
        for (size_t i = 0; i < pallete.size(); ++i)
        {
            if (pallete[i].refcount == 0)
            {
                pallete[i].voxel = voxel;
                pallete[i].refcount = 1;
                return i;
            }
        }

        // no free entry found — grow palette
        size_t newIndex = pallete.size();
        pallete.push_back({ .refcount = 1, .voxel = voxel });

        // check if we exceeded the current bit capacity
        if ((1ULL << indicesLength) <= newIndex)
        {
            indicesLength++;

            growData();
        }

        return newIndex;
    }

    void VoxelStorage::growData()
    {
        BitArray newData(size * indicesLength);
        for (size_t i = 0; i < size; ++i)
        {
            size_t oldIndex = data.readBits(i * (indicesLength - 1), indicesLength - 1);
            newData.writeBits(i * indicesLength, indicesLength, oldIndex);
        }
        data = std::move(newData);
    }

    void VoxelStorage::fitData()
    {
        std::vector<PalleteEntry> newPalette;
        std::unordered_map<size_t, size_t> oldToNewIndex;

        for (size_t i = 0; i < pallete.size(); ++i) {
            if (pallete[i].refcount > 0) {
                oldToNewIndex[i] = newPalette.size();
                newPalette.push_back(pallete[i]);
            }
        }
        size_t usedEntries = newPalette.size();
        int newIndicesLength = 1;
        while ((1ULL << newIndicesLength) < usedEntries) {
            ++newIndicesLength;
        }

        BitArray newData(size * newIndicesLength);

        for (size_t i = 0; i < size; ++i) {
            size_t oldIndex = data.readBits(i * indicesLength, indicesLength);
            size_t newIndex = oldToNewIndex[oldIndex];
            newData.writeBits(i * newIndicesLength, newIndicesLength, newIndex);
        }

        pallete = std::move(newPalette);
        data = std::move(newData);
        indicesLength = newIndicesLength;
    }
}