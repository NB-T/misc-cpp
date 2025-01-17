#include <algorithm>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "nbtlog.hpp"

// namespace nbtlog
//{
// inline const double timestamp() noexcept;
// void log(const std::string& m, const std::optional<int>& start = std::nullopt, const std::optional<int>& end = std::nullopt);
// }

// Function to generate a single random string of a specified length
std::string genRandStr(size_t length)
{
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static const size_t charsetSize = sizeof(charset) - 1;

    // Random number generator
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i)
    {
        randomString += charset[distribution(generator)];
    }

    return randomString;
}

std::vector<std::string> genRandStrs(size_t n, size_t length)
{
    std::vector<std::string> randomStrings;
    randomStrings.reserve(n);

    for (size_t i = 0; i < n; ++i)
    {
        randomStrings.push_back(genRandStr(length));
    }

    return randomStrings;
}

int main()
{
    auto strs = genRandStrs(1000000, 25);
    auto ct = strs.size();
    strs.resize(10 * ct);
    std::copy_n(strs.begin(), ct, strs.begin() + ct);
    std::random_shuffle(strs.begin(), strs.end());

    std::unordered_map<unsigned int, std::string> m;
    auto start = nbtlog::timestamp();
    for (int i = 0; i < strs.size(); ++i)
    {
        if (m.count(i % ct) == 0)
        {
            m[i % ct] = 1;
        }
    }
    auto end = nbtlog::timestamp();
    nbtlog::log("GUARDED: \t\t\t", start, end);

    start = nbtlog::timestamp();
    for (int i = 0; i < strs.size(); ++i)
    {
        m[i % ct] = 1;
    }
    end = nbtlog::timestamp();

    nbtlog::log("UNGUARDED: \t\t\t", start, end);

    return 0;
}
