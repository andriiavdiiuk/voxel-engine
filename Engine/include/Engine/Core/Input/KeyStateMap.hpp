#pragma once
#include <unordered_map>
#include "KeyState.hpp"

namespace Engine
{
    template<typename T>
    class KeyStateMap
    {
    public:
        KeyStateMap() = default;
        ~KeyStateMap() = default;

        void clear()
        {
            keyStateMap.clear();
        }

        KeyState getState(T key) const
        {
            auto it = keyStateMap.find(key);
            if (it == keyStateMap.end())
            {
                return KeyState::Up;
            }
            return it->second;
        }

        void setState(T key, KeyState keyState)
        {
            keyStateMap[key] = keyState;
        }

        void update()
        {
            for (auto& [key, state] : keyStateMap)
            {
                switch (state)
                {
                case KeyState::Pressed:
                    state = KeyState::Down;
                    break;
                case KeyState::Released:
                    state = KeyState::Up;
                    break;
                }
            }
        }

    private:
        std::unordered_map<T, KeyState> keyStateMap;
    };
}