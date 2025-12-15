#pragma once
#include <cstdint>
namespace Engine
{
    enum class KeyState : std::uint8_t
    {
        Up,
        Down,
        Pressed,
        Released,
    };
}