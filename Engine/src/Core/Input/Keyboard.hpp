#pragma once
#include "Key.hpp"
#include "Core/Input/KeyStateMap.hpp"
#include "Common/Bimap.hpp"

namespace GameEngine
{
    class Keyboard 
    {
    public:
        Keyboard() = default;
        ~Keyboard() = default;
        bool isKeyDown(Key key) const;
        bool isKeyPressed(Key key) const;
        bool isKeyReleased(Key key) const;
        bool isKeyUp(Key key) const;
        void update();
        void onKey(int key, int scancode, int action, int mods);

    private:
        KeyStateMap<Key> currentState;
        static Bimap<Key, int> keyMap;
    };
}