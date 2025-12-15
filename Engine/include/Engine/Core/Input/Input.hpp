#pragma once
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Engine
{
    class Input
    {
    public:
        Input() = default;
        ~Input() = default;
        const Keyboard& getKeyboard() const;
        Keyboard& getKeyboard();
        const Mouse& getMouse() const;
        Mouse& getMouse();
        void update();

    private:
        Keyboard keyboard;
        Mouse mouse;
    };

}