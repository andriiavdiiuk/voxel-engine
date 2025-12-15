#pragma once
#include <string>

namespace GameEngine
{
    constexpr std::string_view AssetsRelativePath = GAMEENGINE_ASSETS_RELATIVE_PATH;
    constexpr std::string_view DefaultShaderRegistryPath = GAMEENGINE_ASSETS_RELATIVE_PATH "/registries/shader_registry.json";
    constexpr std::string_view OpenSansTtfFontPath = GAMEENGINE_ASSETS_RELATIVE_PATH "/fonts/OpenSans.ttf";
}