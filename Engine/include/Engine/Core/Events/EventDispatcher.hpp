#pragma once
#include <unordered_map>
#include <functional>

template<typename T>
class EventDispatcher
{
public:
    using Handler = std::function<void(const T&)>;

    size_t subscribe(Handler handler)
    {
        size_t id = nextId++;
        handlers[id] = std::move(handler);
        return id;
    }

    void unsubcribe(size_t handle)
    {
        handlers.erase(handle);
    }

    void dispatch(const T& data) const
    {
        for (const auto& [handle, handler] : handlers)
        {
            handler(data);
        }
    }

private:
    std::unordered_map<size_t, Handler> handlers;
    size_t nextId = 0;
};