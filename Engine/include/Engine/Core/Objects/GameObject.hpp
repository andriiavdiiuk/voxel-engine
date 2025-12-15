#pragma once

namespace Engine
{
    class GameObject
    {
    public:
        virtual ~GameObject() {};
        virtual void update(double deltaTime) = 0;
    };
}