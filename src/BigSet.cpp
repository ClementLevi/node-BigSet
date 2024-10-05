#include "BigSet.h"

// 构造函数
BigSet::BigSet() : length(0), curr_set(0)
{
    sets.push_back({});
    sets_sizes.push_back(0);
}

// 添加值
void BigSet::add(const std::string &value)
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

// 检查是否存在
bool BigSet::has(const std::string &value)
{
    std::string hash = createHash(value);
    if (!sets[curr_set].count(hash))
    {
        return false;
    }
    const auto &valuesArray = sets[curr_set][hash];
    return std::find(valuesArray.begin(), valuesArray.end(), value) != valuesArray.end();
}

// 删除值
void BigSet::deleteValue(const std::string &value, Napi::Env env)
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

// 随机返回一个值
std::string BigSet::random()
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

// 转换为字符串
std::string BigSet::toString()
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

// 获取集合长度
size_t BigSet::getLength()
{
    return length;
}

// 创建哈希
std::string BigSet::createHash(const std::string &input)
{
    std::hash<std::string> hasher;
    return std::to_string(hasher(input));
}

// N-API 绑定代码
Napi::Object CreateBigSet(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    BigSet *bigSet = new BigSet();

    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "instance"), Napi::External<BigSet>::New(env, bigSet));

    // 显式捕获 env
    obj.Set("add", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                       {
        Napi::String value = info[0].As<Napi::String>();
        bigSet->add(value.Utf8Value()); }));

    obj.Set("has", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                       {
        Napi::String value = info[0].As<Napi::String>();
        return Napi::Boolean::New(env, bigSet->has(value.Utf8Value())); }));

    obj.Set("delete", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                          {
        Napi::String value = info[0].As<Napi::String>();
        bigSet->deleteValue(value.Utf8Value(), env); }));

    obj.Set("random", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                          { return Napi::String::New(env, bigSet->random()); }));

    obj.Set("toString", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                            { return Napi::String::New(env, bigSet->toString()); }));

    obj.Set("getLength", Napi::Function::New(env, [bigSet, env](const Napi::CallbackInfo &info)
                                             { return Napi::Number::New(env, bigSet->getLength()); }));

    return obj; // 返回这个对象
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("BigSet", Napi::Function::New(env, CreateBigSet, "BigSet"));
    return exports;
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return Init(env, exports);
}

NODE_API_MODULE(bigset, InitAll)