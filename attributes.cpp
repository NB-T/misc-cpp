#include <algorithm>
#include <iostream>

#include "nbtlog.hpp"

int main()
{
    // Generate data
    const unsigned arraySize = 32768;
    int data[arraySize];

    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = std::rand() % 256;

    // Test
    auto start = nbtlog::timestamp();
    long long sum = 0;
    for (unsigned i = 0; i < 100000; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {                        // Primary loop.
            if (data[c] >= 100)  // [[likely]]
                sum += data[c];
        }
    }

    auto elapsedTime = nbtlog::timestamp() - start;
    nbtlog::log(std::to_string(sum), elapsedTime);

    // !!! With this, the next loop runs faster.
    std::sort(data, data + arraySize);

    // Test
    start = nbtlog::timestamp();
    sum = 0;
    for (unsigned i = 0; i < 100000; ++i)
    {
        for (unsigned c = 0; c < arraySize; ++c)
        {                        // Primary loop.
            if (data[c] >= 100)  // [[likely]]
                sum += data[c];
        }
    }

    elapsedTime = nbtlog::timestamp() - start;
    nbtlog::log(std::to_string(sum), elapsedTime);
}
