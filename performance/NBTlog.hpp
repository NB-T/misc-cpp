#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>

namespace detail
{
template <typename D>
consteval const char* suffix()
{
    if constexpr (std::is_same_v<D, std::chrono::nanoseconds>)
        return "ns";
    else if constexpr (std::is_same_v<D, std::chrono::microseconds>)
        return "us";
    else if constexpr (std::is_same_v<D, std::chrono::milliseconds>)
        return "ms";
    else if constexpr (std::is_same_v<D, std::chrono::seconds>)
        return "s";
    else if constexpr (std::is_same_v<D, std::chrono::minutes>)
        return "min";
    else if constexpr (std::is_same_v<D, std::chrono::hours>)
        return "h";
}
} // namespace detail

// main data are start time and timestamp function
// loggers also can do messages
template <typename Duration = std::chrono::milliseconds>
class NBTlog
{
  public:
    size_t _duration_()
    {
        return std::chrono::duration_cast<Duration>(CURRENT_TIME() - START_TIME).count();
    }
    NBTlog() : START_TIME(CURRENT_TIME())
    {
    }

    std::chrono::time_point<std::chrono::system_clock> START_TIME;

    std::chrono::time_point<std::chrono::system_clock> CURRENT_TIME()
    {
        return std::chrono::system_clock::now();
    }

    inline void start()
    {
        START_TIME = CURRENT_TIME();
    }

    inline void stamp()
    {
        start();
    }

    inline void log()
    {
        std::cout << "[ dur " << _duration_() << detail::suffix<Duration>() << " ]" << std::endl
                  << std::endl;
    }

    inline void log(const std::string& message)
    {
        std::cout << "[ " << message << " ]" << std::endl
                  << "[ dur " << _duration_() << detail::suffix<Duration>() << " ]" << std::endl
                  << std::endl;
    }
};

using nano = NBTlog<std::chrono::nanoseconds>;
using micro = NBTlog<std::chrono::microseconds>;
using milli = NBTlog<std::chrono::milliseconds>;
using sec = NBTlog<std::chrono::seconds>;
using min = NBTlog<std::chrono::minutes>;
using hr = NBTlog<std::chrono::hours>;
