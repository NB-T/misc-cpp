#include <iostream>

#include "nbtlog.hpp"

void prevent_optimization()
{
}

int main()
{
    auto start = nbtlog::timestamp();
    for (int i = 0; i < 10000000; ++i)
    {
    }

    nbtlog::log("empty", nbtlog::timestamp() - start);

    start = nbtlog::timestamp();
    for (volatile int i = 0; i < 10000000; ++i)
    {
    }

    nbtlog::log("volatile", nbtlog::timestamp() - start);

    return EXIT_SUCCESS;
}
