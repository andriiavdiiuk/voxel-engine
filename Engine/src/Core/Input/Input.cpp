#include "Engine/Core/Input/Input.hpp"

namespace Engine
{
    void Input::update()
    {
        keyboard.update();
        mouse.update();
    }

    const Keyboard& Input::getKeyboard() const
    {
        return keyboard;
    }

    Keyboard& Input::getKeyboard()
    {
        return keyboard;
    }

    const Mouse& Input::getMouse() const
    {
        return mouse;
    }
    Mouse& Input::getMouse()
    {
        return mouse;
    }
}