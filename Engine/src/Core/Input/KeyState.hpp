#pragma once
#include <cstdint>
namespace GameEngine
{
    enum class KeyState : std::uint8_t
    {
        Up,
        Down,
        Pressed,
        Released,
    };
}