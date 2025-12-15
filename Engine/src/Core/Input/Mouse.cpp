#include "Engine/Core/Input/Mouse.hpp"
#include <GLFW/glfw3.h>

namespace Engine
{
    static bool firstMouse = false;
    bool Mouse::isKeyDown(MouseButton key) const
    {
        auto state = currentState.getState(key);
        return state == KeyState::Down || state == KeyState::Pressed;
    }

    bool Mouse::isKeyPressed(MouseButton key) const
    {
        return currentState.getState(key) == KeyState::Pressed;
    }

    bool Mouse::isKeyReleased(MouseButton key) const
    {
        return currentState.getState(key) == KeyState::Released;
    }

    bool Mouse::isKeyUp(MouseButton key) const
    {
        return currentState.getState(key) == KeyState::Up;
    }

    glm::vec2 Mouse::getCursorPosition() const
    {
        return currentCursorPosition;
    }

    glm::dvec2 Mouse::getDeltaMovement() const
    {
        return deltaMovement;
    }

    glm::dvec2 Mouse::getScrollOffset() const
    {
        return scrollOffset;
    }

    void Mouse::update()
    {
        deltaMovement = currentCursorPosition - lastCursorPosition;
        lastCursorPosition = currentCursorPosition;

        currentState.update();
    }

    void Mouse::onKey(int key, int action, int mods)
    {
        MouseButton mappedKey = keyMap.get(key);
        switch (action)
        {
        case GLFW_PRESS:
            currentState.setState(mappedKey, KeyState::Pressed);
            break;
        case GLFW_REPEAT:
            currentState.setState(mappedKey, KeyState::Down);
            break;
        case GLFW_RELEASE:
            currentState.setState(mappedKey, KeyState::Released);
            break;
        }
    }

    void Mouse::onCursorPosition(double xpos, double ypos)
    {
        currentCursorPosition = { xpos, ypos };
    }

    void Mouse::onScroll(double xoffset, double yoffset)
    {
        scrollOffset.x = xoffset;
        scrollOffset.y = yoffset;
    }

    Bimap<MouseButton, int> Mouse::keyMap = {
        { MouseButton::Left, GLFW_MOUSE_BUTTON_LEFT  },
        { MouseButton::Right, GLFW_MOUSE_BUTTON_RIGHT },
        { MouseButton::Middle, GLFW_MOUSE_BUTTON_MIDDLE },
        { MouseButton::Button1, GLFW_MOUSE_BUTTON_1 },
        { MouseButton::Button2, GLFW_MOUSE_BUTTON_2 },
        { MouseButton::Button3, GLFW_MOUSE_BUTTON_3 },
        { MouseButton::Button4, GLFW_MOUSE_BUTTON_4 },
        { MouseButton::Button5, GLFW_MOUSE_BUTTON_5 },
        { MouseButton::Button6, GLFW_MOUSE_BUTTON_6 },
        { MouseButton::Button7, GLFW_MOUSE_BUTTON_7 },
        { MouseButton::Button8, GLFW_MOUSE_BUTTON_8 },
    };
}