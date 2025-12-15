#pragma once
#include <string>
namespace Engine
{
    struct AssetHandle
    {
        size_t id;

        AssetHandle(size_t _id = 0) : id(_id) {}

        bool operator==(const AssetHandle& other) const { return id == other.id; }
        bool operator==(const size_t& other) const { return id == other; }

        bool isValid() const { return id != 0; }

        static AssetHandle fromString(const std::string& str)
        {
            static std::hash<std::string> hasher;
            return AssetHandle(hasher(str));
        }
    };
}
//std::ostream& operator<<(std::ostream& os, const GameEngine::AssetHandle& handle) {
//    return os << handle.id;
//}
namespace std {
    template<>
    struct hash<Engine::AssetHandle> {
        std::size_t operator()(const Engine::AssetHandle& h) const noexcept {
            return h.id;
        }
    };
}