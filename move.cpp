#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "nbtlog.hpp"

const int N = 100000000;

int main()
{
    std::vector<int> v1(N);
    std::iota(std::begin(v1), std::end(v1), 0);

    std::vector<int> v2(N, 0);

    auto t1 = nbtlog::timestamp();
    std::vector<int> tmp1(v1);
    v1 = v2;
    v2 = tmp1;
    nbtlog::log("NO MOVE", t1, nbtlog::timestamp());

    std::swap(v1, v2);

    t1 = nbtlog::timestamp();
    std::vector<int> tmp2(std::move(v1));
    v1 = std::move(v2);
    v2 = std::move(tmp2);
    nbtlog::log("MOVE", t1, nbtlog::timestamp());

    return EXIT_SUCCESS;
}
