#include <napi.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <random>

class BigSet
{
public:
    BigSet() : length(0), curr_set(0)
    {
        sets.push_back({});
        sets_sizes.push_back(0);
    }

    void add(const std::string &value)
    {
        std::string hash = createHash(value);

        if (sets[curr_set].count(hash) && sets[curr_set][hash].size() >= SET_CAPACITY)
        {
            curr_set++;
            sets.push_back({});
            sets_sizes.push_back(0);
        }

        if (!sets[curr_set].count(hash))
        {
            sets[curr_set][hash] = {};
        }

        auto &valuesArray = sets[curr_set][hash];
        if (std::find(valuesArray.begin(), valuesArray.end(), value) == valuesArray.end())
        {
            valuesArray.push_back(value);
            sets_sizes[curr_set]++;
            length++;
        }
    }

    bool has(const std::string &value)
    {
        std::string hash = createHash(value);
        if (!sets[curr_set].count(hash))
        {
            return false;
        }
        const auto &valuesArray = sets[curr_set][hash];
        return std::find(valuesArray.begin(), valuesArray.end(), value) != valuesArray.end();
    }

    void deleteValue(const std::string &value, Napi::Env env)
    {
        if (!has(value))
        {
            Napi::TypeError::New(env, "Value does not exist.").ThrowAsJavaScriptException();
            return;
        }

        std::string hash = createHash(value);
        auto &valuesArray = sets[curr_set][hash];
        auto position = std::find(valuesArray.begin(), valuesArray.end(), value);

        if (position != valuesArray.end())
        {
            valuesArray.erase(position);
            sets_sizes[curr_set]--;
            length--;
        }
    }

    std::string random()
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        size_t randomSetIndex = std::uniform_int_distribution<size_t>(0, sets.size() - 1)(gen);
        const auto &randomSet = sets[randomSetIndex];

        if (randomSet.empty())
        {
            return ""; // 可以根据需要抛出异常
        }

        std::vector<std::string> keys;
        for (const auto &pair : randomSet)
        {
            keys.push_back(pair.first);
        }

        std::string randomKey = keys[std::uniform_int_distribution<size_t>(0, keys.size() - 1)(gen)];
        const auto &randomValuesArray = randomSet.at(randomKey);

        return randomValuesArray[std::uniform_int_distribution<size_t>(0, randomValuesArray.size() - 1)(gen)];
    }

    std::string toString()
    {
        std::string result;
        for (const auto &set : sets)
        {
            for (const auto &pair : set)
            {
                for (const auto &value : pair.second)
                {
                    result += value + ", ";
                }
            }
        }
        return result;
    }

    size_t getLength()
    {
        return length;
    }

private:
    static const size_t SET_CAPACITY = 65535;
    size_t length;
    size_t curr_set;
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> sets;
    std::vector<size_t> sets_sizes;

    std::string createHash(const std::string &input)
    {
        // 这里可以用任何哈希函数替代，比如 SHA256
        std::hash<std::string> hasher;
        return std::to_string(hasher(input));
    }
};

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    auto *bigSet = new BigSet();

    exports.Set("add", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                           {
        Napi::String value = info[0].As<Napi::String>();
        bigSet->add(value.Utf8Value()); }));

    exports.Set("has", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                           {
        Napi::String value = info[0].As<Napi::String>();
        return Napi::Boolean::New(env, bigSet->has(value.Utf8Value())); }));

    exports.Set("delete", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                              {
        Napi::String value = info[0].As<Napi::String>();
        bigSet->deleteValue(value.Utf8Value(), env); }));

    exports.Set("random", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                              { return Napi::String::New(env, bigSet->random()); }));

    exports.Set("toString", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                                { return Napi::String::New(env, bigSet->toString()); }));

    exports.Set("getLength", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                                 { return Napi::Number::New(env, bigSet->getLength()); }));

    return exports;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return Init(env, exports);
}

NODE_API_MODULE(bigset, InitAll)
