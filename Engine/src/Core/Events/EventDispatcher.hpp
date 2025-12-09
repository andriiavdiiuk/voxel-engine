#pragma once
#include <vector>
#include <functional>

template<typename T>
class EventDispatcher
{
public:
    using Handler = std::function<void(const T&)>;

    void subscribe(Handler handler)
    {
        handlers.push_back(handler);
    }
    void dispatch(const T& data) const
    {
        for (const auto& handler : handlers)
        {
            handler(data);
        }
    }

private:
    std::vector<Handler> handlers;
};