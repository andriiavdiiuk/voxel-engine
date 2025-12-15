#pragma once
#include "Engine/Core/Logger.hpp"
#include "AssetHandle.hpp"
#include <functional>
#include <unordered_map>

namespace Engine
{
    template<typename T>
    class AssetStorage
    {
    public:
        struct AssetMetadata
        {
            std::string name;
            std::string path;
        };

        using AssetLoaderType = std::function<std::shared_ptr<T>(const std::string&)>;

        using AssetRegistriesList = std::initializer_list<std::reference_wrapper<const std::unordered_map<std::string, std::string>>>;

        AssetStorage(AssetLoaderType loader) : loader(std::move(loader)) {};

        AssetStorage(const std::unordered_map<std::string, std::string>& registry, AssetLoaderType loader) : loader(std::move(loader))
        {
            for (const auto& [name, path] : registry)
            {
                registerAsset(name, path);
            }
        };

        AssetStorage(AssetRegistriesList registries, AssetLoaderType loader) : loader(std::move(loader))
        {
            for (const auto& registryRef : registries)
            {
                const auto& registry = registryRef.get();
                for (const auto& [name, path] : registry)
                {
                    registerAsset(name, path);
                }
            }
        };

        void loadAll()
        {
            for (auto& [id, asset] : assets)
            {
                loadedAssets[id] = loader(asset.path);
                LOG_INFO("Asset {} loaded", asset.name);
            }
        }

        void load(const AssetHandle& handle)
        {
            auto assetIt = assets.find(handle);
            if (assetIt == assets.end())
            {
                LOG_ERROR("Asset not found for handle {}", handle.id);
                throw std::runtime_error("Asset not found");
            }

            AssetMetadata& asset = assetIt->second;
            loadedAssets[handle] = loader(asset.path);
            LOG_INFO("Asset {} loaded", asset.name);
        }

        void load(const std::string& name)
        {
            load(AssetHandle::fromString(name));
        }

        void unload(const AssetHandle& handle)
        {
            auto it = assets.find(handle);
            if (it != assets.end())
                LOG_INFO("Asset {} unloaded", it->second.name);

            loadedAssets.erase(handle);
        }

        void unload(const std::string& name)
        {
            unload(AssetHandle::fromString(name));
        }

        bool isLoaded(const AssetHandle& handle) const
        {
            return loadedAssets.find(handle) != loadedAssets.end();
        }

        void registerAsset(const std::string& name, const std::string& path)
        {
            AssetHandle handle = AssetHandle::fromString(name);
            if (assets.find(handle) != assets.end())
            {
                std::string msg = "Asset '" + name + "' already registered";
                LOG_ERROR(msg);
                throw std::runtime_error(msg);
            }

            assets[handle] = { name, path };
        }

        std::shared_ptr<T> getAsset(const AssetHandle& handle)
        {
            if (!isLoaded(handle))
                load(handle);
            return loadedAssets[handle];
        }

        std::shared_ptr<T> getAsset(const std::string& name)
        {
            return getAsset(AssetHandle::fromString(name));
        }

        AssetHandle getAssetHandle(const std::string& name)
        {
            auto handle = AssetHandle::fromString(name);
            auto assetIt = assets.find(handle);
            if (assetIt == assets.end())
            {
                LOG_ERROR("Asset not found for handle {}", handle.id);
                throw std::runtime_error("Asset not found");
            }
            
            return handle;
        }

    private:
        AssetLoaderType loader;
        std::unordered_map<AssetHandle, std::shared_ptr<T>> loadedAssets;
        std::unordered_map<AssetHandle, AssetMetadata> assets;
    };

}