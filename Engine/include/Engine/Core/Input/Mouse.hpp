#pragma once
#include "Engine/Core/Input/KeyStateMap.hpp"
#include "Engine/Common/Bimap.hpp"
#include <glm.hpp>
#include "MouseButton.hpp"

namespace Engine
{
    class Mouse
    {
    public:
        Mouse() = default;
        ~Mouse() = default;
        bool isKeyDown(MouseButton key) const;
        bool isKeyPressed(MouseButton key) const;
        bool isKeyReleased(MouseButton key) const;
        bool isKeyUp(MouseButton key) const;
        glm::vec2 getCursorPosition() const;
        glm::dvec2 getDeltaMovement() const;
        glm::dvec2 getScrollOffset() const;
        void update();
        void onKey(int key, int action, int mods);
        void onCursorPosition(double xpos, double ypos);
        void onScroll(double xoffset, double yoffset);

    private:
        KeyStateMap<MouseButton> currentState;
        static Bimap<MouseButton, int> keyMap;
        glm::dvec2 lastCursorPosition = glm::dvec2(0.0);
        glm::dvec2 deltaMovement = glm::dvec2(0.0);
        glm::dvec2 currentCursorPosition = glm::dvec2(0.0);
        glm::dvec2 scrollOffset = glm::dvec2(0.0);
    };
}