#pragma once

namespace GameEngine
{
    class GameObject
    {
    public:
        virtual ~GameObject() {};
        virtual void update(double deltaTime) = 0;
    };
}