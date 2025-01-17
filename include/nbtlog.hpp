#pragma once

#include <omp.h>

#include <chrono>
#include <iostream>
#include <optional>

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

void log(const std::string& m, const std::optional<int>& start = std::nullopt, const std::optional<int>& end = std::nullopt);
void log(const std::string& m, int elapsedTime);
void log(int elapsedTime);
}
