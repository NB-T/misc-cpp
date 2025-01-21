#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include "nbtlog.hpp"

std::vector<int> insert(int x, std::vector<int>& v)
{
    if (v.empty())
    {
        return {x};
    }

    else
    {
        int v0 = v[v.size() - 1];
        v.pop_back();
        if (x <= v0)
        {
            std::vector<int> r = {x, v0};
            r.insert(std::end(r), std::begin(v), std::end(v));
            return r;
        }
        else
        {
            std::vector<int> r = {v0};
            auto v1 = insert(v0, v);
            r.insert(std::end(r), std::begin(v1), std::end(v1));
            return r;
        }
    }
}

std::vector<int>
insertion_sort(std::vector<int>& v)
{
    if (v.empty())
    {
        return v;
    }

    int v0 = v[v.size() - 1];
    v.pop_back();

    return insert(v0, v);
}

std::vector<int> quicksort(std::vector<int>& v)
{
    if (v.empty())
    {
        return v;
    }

    else
    {
        int v0 = v[0];

        std::vector<int> r;
        std::copy_if(std::begin(v), std::end(v), std::back_inserter(r), [&v0](int i)
                     { return i <= v0; });
        r.push_back(v0);
        std::copy_if(std::begin(v), std::end(v), std::back_inserter(r), [&v0](int i)
                     { return i > v0; });
        return r;
    }
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    std::vector<int> v1(n);

    std::iota(std::begin(v1), std::end(v1), 1);
    std::random_shuffle(std::begin(v1), std::end(v1));

    std::vector<int> v2 = v1;

    auto start = nbtlog::timestamp();

    quicksort(v1);

    nbtlog::log("QUICKSORT", nbtlog::timestamp() - start);

    start = nbtlog::timestamp();

    insertion_sort(v2);

    nbtlog::log("INSERTION SORT", nbtlog::timestamp() - start);

    return EXIT_SUCCESS;
}
