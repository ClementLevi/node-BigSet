#ifndef BIGSET_H
#define BIGSET_H

#include <napi.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <random>

// BigSet 类定义
class BigSet {
public:
    BigSet();
    void add(const std::string &value);
    bool has(const std::string &value);
    void deleteValue(const std::string &value, Napi::Env env);
    std::string random();
    std::string toString();
    size_t getLength();

private:
    static const size_t SET_CAPACITY = 65535;
    size_t length;
    size_t curr_set;
    std::vector<std::unordered_map<std::string, std::vector<std::string>>> sets;
    std::vector<size_t> sets_sizes;

    std::string createHash(const std::string &input);
};

#endif // BIGSET_H
