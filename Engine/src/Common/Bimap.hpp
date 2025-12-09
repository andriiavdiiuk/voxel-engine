#pragma once
#include <map>
#include <vector>
#include <utility>
#include <initializer_list>
#include <stdexcept>

template<typename Key, typename Value>
class Bimap
{
    std::vector<std::pair<Key, Value>> data;
    std::map<Key, size_t> mapValueByKey;
    std::map<Value, size_t> mapKeyByValue;

public:
    Bimap() = default;

    Bimap(std::initializer_list<std::pair<const Key, Value>> list) {
        for (const auto& [key, value] : list) {
            insert(key, value);
        }
    }
    void clear()
    {
        mapValueByKey.clear();
        mapKeyByValue.clear();
        data.clear();
    }

    void insert(const Key& key, const Value& value)
    {
        data.emplace_back(std::make_pair( key, value ));
        size_t pos = data.size() - 1;
        mapValueByKey[key] = pos;
        mapKeyByValue[value] = pos;
    }

    Value get(const Key& key)
    {
        auto it = mapValueByKey.find(key);
        if (it == mapValueByKey.end())
            throw std::out_of_range("Key not found");
        return data[it->second].second;
    }
    Key get(const Value& value)
    {
        auto it = mapKeyByValue.find(value);
        if (it == mapKeyByValue.end())
            throw std::out_of_range("Value not found");
        return data[it->second].first;
    }
};