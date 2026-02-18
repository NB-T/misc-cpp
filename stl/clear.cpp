#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#include "nbtlog.hpp"

int main()
{
    std::queue<int> q;

    for (int i = 0; i < 1000000000; ++i)
    {
        q.push(i);
    }

    auto start = nbtlog::timestamp();
    std::queue<int> empty_q;
    std::swap(q, empty_q);
    nbtlog::log("CLEAR QUEUE 1000000000", nbtlog::timestamp() - start);
}
