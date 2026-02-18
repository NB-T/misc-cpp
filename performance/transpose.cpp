#include <iostream>
#include <vector>

#include "nbtlog.hpp"

int main()
{
    for (int n = 1000; n < 10000; n *= 2)
    {
        std::cout << "~~~~~~~~~~N~~~~~~~~~~" << '\t' << n << "\n\n";
        std::vector<std::vector<int>> mul(n, std::vector<int>(n, 0));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                mul[i][j] = i + j;
            }
        }

        auto start = nbtlog::timestamp();
        std::vector<std::vector<int>> tmp(n, std::vector<int>(n));
        nbtlog::log("allocation", nbtlog::timestamp() - start);
        start = nbtlog::timestamp();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                tmp[i][j] = mul[j][i];
            }
        }
        nbtlog::log("out-of-place transpose", nbtlog::timestamp() - start);

        tmp = mul;
        start = nbtlog::timestamp();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                std::swap(tmp[i][j], tmp[j][i]);
            }
        }
        nbtlog::log("in-place transpose", nbtlog::timestamp() - start);
        std::cout << "\n\n\n";
    }

    return EXIT_SUCCESS;
}
