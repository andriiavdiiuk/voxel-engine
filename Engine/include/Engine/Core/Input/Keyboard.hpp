#pragma once
#include "Key.hpp"
#include "Engine/Core/Input/KeyStateMap.hpp"
#include "Engine/Common/Bimap.hpp"

namespace Engine
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