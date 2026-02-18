#include <iostream>
#include <numeric>
#include <vector>

#include "nbtlog.hpp"

template <typename T>
std::vector<T> flatten(std::vector<std::vector<T>>& input)
{
    // in reverse order, eliminate zero vectors until first nonzero vector
    // at least in case there are more threads than reads
    /* for (int i = input.size() - 1; i >= 0; --i)
    {
        if (input[i].size() == 0)
        {
            input.erase(input.begin() + i);
        }
        else
        {
            break;
        }
    } */
    while (input.size() > 0 && input.back().size() == 0)
    {
        input.pop_back();
    }

    size_t total_size = 0;
    std::vector<size_t> offsets(input.size(), 0);

#if DEBUG
    std::cout << "nthreads " << input.size() << std::endl;
    std::cout << "input size: " << input.size() << std::endl;
#endif

    // total size and offsets for each sub-vector
    for (size_t i = 0; i < input.size(); ++i)
    {
        offsets[i] = total_size;
        total_size += input[i].size();

#if DEBUG
        std::cout << "sub size " << i << ": " << input[i].size() << std::endl;
#endif
    }

    std::vector<int> output(total_size);

// parallelize flattening
#pragma omp parallel for schedule(static)
    for (size_t i = 0; i < input.size(); ++i)
    {
        // move from input[i] to correct position in output
        std::move(input[i].begin(), input[i].end(), output.begin() + offsets[i]);
    }

    return output;
}

int main()
{
    /* std::iota(std::begin(v1), std::end(v1), 1);
    std::random_shuffle(std::begin(v1), std::end(v1)); */

    // create some vectors
    // flatten them
    // time

    std::vector<std::vector<int>> input(5);
    for (size_t i = 0; i < input.size(); ++i)
    {
        input[i] = std::vector<int>(5);
        std::iota(std::begin(input[i]), std::end(input[i]), 1);
        std::random_shuffle(std::begin(input[i]), std::end(input[i]));
    }

    // print input
    for (size_t i = 0; i < input.size(); ++i)
    {
        for (size_t j = 0; j < input[i].size(); ++j)
        {
            std::cout << input[i][j] << " ";
        }
        std::cout << std::endl;
    }

    auto start = nbtlog::timestamp();
    auto result = flatten(input);
    // sum of result
    // int sum = std::accumulate(std::begin(result), std::end(result), 0);
    auto end = nbtlog::timestamp();

    // print flattened
    for (size_t i = 0; i < result.size(); ++i)
    {
        std::cout << result[i] << " ";
    }

    nbtlog::log("FLATTEN", end - start);

    start = nbtlog::timestamp();
    // get sum of unflattened stuff
    int sum2 = 0;
    for (size_t i = 0; i < input.size(); ++i)
    {
        sum2 += std::accumulate(std::begin(input[i]), std::end(input[i]), 0);
    }
    end = nbtlog::timestamp();

    nbtlog::log("SUM", end - start);
}