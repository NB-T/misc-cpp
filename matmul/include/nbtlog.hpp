#pragma once
#include <omp.h>

#include <chrono>
#include <iostream>
#include <optional>
#include <sstream>

namespace nbtlog
{
inline double timestamp() noexcept
{
    // return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_cl
    // ock::now()
    //.time_since_epoch())
    //.count();
    return omp_get_wtime() * 1000;
};

// refactor:
// should be able to do things like this:
// log("hello", "world", "thingy", <elapsed time>);
// log(<elapsed time>);
// log("hello", "world");
// using same formatting (nice tilde borders, etc.)

/*
template <typename getStringified>
std::string toStringAny(const getStringified& s)
{
    std::ostringstream oss;
    oss << s;
    return oss.str();
}

template <typename... Args>
void log(Args... args)
{
    // length of args for border
    int length = 0;
    ((length += toStringAny(args).length()), ...);
    std::cout << std::string(length + 4, '~') << std::endl;
    (std::cout << ... << args) << std::endl;
    std::cout << std::string(length + 4, '~') << std::endl;
}
*/

void log(const std::string& m, const std::optional<int>& start = std::nullopt, const std::optional<int>& end = std::nullopt);
void log(int elapsedTime);
}
