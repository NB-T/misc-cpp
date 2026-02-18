#include <cstring>
#include <iostream>

#include "nbtlog.hpp"

int f(int i)
{
    return i;
}

int g(int i)
{
    return -i;
}

int main()
{
    //    int* arr = new int[1500000];
    //   std::memset(arr, 500, 1500000);
    int arr[1500000];
    std::memset(&arr, 500, 1500000);

    auto start = nbtlog::timestamp();
    for (int i = 0; i < 1500000; ++i)
    {
        arr[i] -= f(i);
        arr[i] += g(i);
    }
    nbtlog::log("COMBINED", nbtlog::timestamp() - start);

    //  std::memset(arr, 500, 1500000);
    std::memset(&arr, 500, 1500000);

    start = nbtlog::timestamp();
    for (int i = 0; i < 1500000; ++i)
    {
        arr[i] -= f(i);
    }

    for (int i = 0; i < 1500000; ++i)
    {
        arr[i] += g(i);
    }
    nbtlog::log("SEPARATE", nbtlog::timestamp() - start);

    // delete[] arr;

    return EXIT_SUCCESS;
}
