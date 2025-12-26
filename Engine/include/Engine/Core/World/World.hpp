#pragma once
#include "Level.hpp"
#include "vector"
#include <memory>

namespace Engine
{
    class World
    {
    public:
        std::vector<std::unique_ptr<Level>> levels;
    };
}