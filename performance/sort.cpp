#include "../external/parlaylib/examples/mergesort.h"
#include "../external/parlaylib/include/parlay/parallel.h"
#include "../external/parlaylib/include/parlay/primitives.h"
#include "../external/parlaylib/include/parlay/sequence.h"
#include <omp.h>
#include <random>
#include <vector>

void merge_sort_recursive(int* begin, int* end)
{
    const auto size = end - begin;

    // Sequential threshold to mitigate task overhead if (size < 1024)
    {
        std::sort(begin, end);
        return;
    }

    int* mid = begin + size / 2;

#pragma omp task shared(begin, mid)
    merge_sort_recursive(begin, mid);

#pragma omp task shared(mid, end)
    merge_sort_recursive(mid, end);

#pragma omp taskwait
    std::inplace_merge(begin, mid, end);
}

void parallel_merge_sort(std::vector<int>& v)
{
    if (v.empty())
        return;

#pragma omp parallel
#pragma omp single
    merge_sort_recursive(v.data(), v.data() + v.size());
}

int main()
{
    std::cout << "omp_get_max_threads " << omp_get_max_threads() << std::endl;
    std::cout << "omp_get_num_threads " << omp_get_num_threads() << std::endl;
    const size_t n = 50000000;
    const unsigned seed = 42;

    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 100000000);

    parlay::sequence<int> data1(n);
    std::vector<int> data2(n);
    std::vector<int> data3(n);
#pragma omp parallel for
    for (size_t i = 0; i < n; ++i)
    {
        data1[i] = dist(gen);
        data2[i] = data1[i];
        data3[i] = data1[i];
    }

    parlay::internal::timer t1("Time 1");
    parlay::internal::timer t2("Time 2");
    parlay::internal::timer t3("Time 3");

    t1.start();
    merge_sort(data1);
    t1.next("mergesort time");

    t2.start();
    std::sort(data2.begin(), data2.end());
    t2.next("stl sort time");

    t3.start();
    parallel_merge_sort(data3);
    t3.next("omp mergesort time");

    return 0;
}
