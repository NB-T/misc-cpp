#include <omp.h>

#include <iostream>

int main()
{
    omp_set_num_threads(4);
#pragma omp parallel
    {
        std::cout << "thread " << omp_get_thread_num() << std::endl;
    }
    std::cout << std::endl;
    // #pragma omp parallel num_threads(8)
    //     {
    //         std::cout << "thread " << omp_get_thread_num() << std::endl;
    //     }
    //     std::cout << std::endl;
    // #pragma omp parallel sections
    //     {
    // #pragma omp section
    //         {
    //             std::cout << "thread " << omp_get_thread_num() << " section 1" << std::endl;
    //         }
    // #pragma omp section
    //         {
    //             std::cout << "thread " << omp_get_thread_num() << " section 2" << std::endl;
    //         }
    //     }
    // #pragma omp parallel
    //    {
    // #pragma omp single
    //        {
    // #pragma omp task
    //            std::cout << "task 1 thread " << omp_get_thread_num() << std::endl;
    // #pragma omp task
    //            std::cout << "task 2 thread " << omp_get_thread_num() << std::endl;
    //        }
    //    }

#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 0; i < 4; ++i)
            {
#pragma omp task
                std::cout << "task " << i << " thread " << omp_get_thread_num() << std::endl;
            }
        }
    }
    return 0;
}
