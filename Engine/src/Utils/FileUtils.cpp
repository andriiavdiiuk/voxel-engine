#include "Engine/Utils/FileUtils.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Engine/Core/Logger.hpp"

namespace Engine
{
    std::string readFile(const std::string& path)
    {
        if (!std::filesystem::exists(path)) {
            LOG_ERROR("file does not exist: {}", path);
            throw std::runtime_error("file does not exist: " + path);
        }

        std::ifstream file(path);
        if (!file) {
            LOG_ERROR("Failed to open file: {}", path);
            throw std::runtime_error("Failed to open file: " + path);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

}