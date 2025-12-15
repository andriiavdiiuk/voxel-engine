#pragma once
#include <string>
#include <unordered_map>
#include "Engine/Core/Resources/AssetHandle.hpp"
namespace Engine
{
    struct Voxel
    {
        /**
         * @brief Store voxel type as @ref AssetHandle "AssetHandle".
         * 
         * Id zero means non-existing voxel (air voxel).
         */
        AssetHandle type = AssetHandle(0);

        bool operator==(const Voxel& voxel) const {
            return type == voxel.type;
        }

        Voxel(AssetHandle handle)
        {
            type = handle;
        }

        Voxel(size_t id)
        {
            type = AssetHandle(id);
        }
    };
}