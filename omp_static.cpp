#include <omp.h>

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

const int DATASIZE = 500;

int main()
{
    std::unordered_map<int, std::set<int>> chunks;
#pragma omp parallel for num_threads(omp_get_max_threads()) schedule(static, DATASIZE / omp_get_max_threads())
    for (int i = 0; i < DATASIZE; ++i)
    {
        // std::cout << "THREAD: " << omp_get_thread_num() << '\t' << i << '\n';
#pragma omp critical
        chunks[omp_get_thread_num()].insert(i);
    }

    for (int i = 0; i < omp_get_max_threads(); ++i)
    {
        std::cout << i << std::endl;
        for (int j : chunks[i])
        {
            std::cout << '\t' << j << std::endl;
        }
    }
    /*
    for (int i : chunks[0])
        {
            std::cout << i << std::endl;
        }
        std::cout << std::endl;
        for (int i : chunks[14])
        {
            std::cout << i << std::endl;
        }
        std::cout << std::endl;
        for (int i : chunks[15])
        {
            std::cout << i << std::endl;
        }
            */

    return EXIT_SUCCESS;
}
