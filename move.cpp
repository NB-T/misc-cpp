#include <iostream>
#include <utility>
#include <vector>

#include "nbtlog.hpp"

int main()
{
    /* big arr[10000];
     * fill with vectors by copy, each of which gets modified at the end
     * then repeat but call move
     */

    std::vector<std::vector<int>> bigv(10000, std::vector<int>(10000, 0));

    auto start = nbtlog::timestamp();

    for (int i = 0; i < 10000; ++i)
    {
        std::vector<int> tmp(10000);
        for (int j = 0; j < 10000; ++j)
        {
            tmp[j] = j;
        }
        bigv[i] = tmp;
    }

    nbtlog::log("NO MOVE", nbtlog::timestamp() - start);

    start = nbtlog::timestamp();
    for (int i = 0; i < 10000; ++i)
    {
        std::vector<int> tmp(10000);
        for (int j = 0; j < 10000; ++j)
        {
            tmp[j] = j;
        }
        bigv[i] = std::move(tmp);
    }

    nbtlog::log("MOVE", nbtlog::timestamp() - start);

    return EXIT_SUCCESS;
}
