#include "../nbtlog/include/nbtlog/NBTlog.hpp"
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

static std::atomic<int> shared_counter{0};

void worker(int thread_id)
{
    for (int i = 0; i < 1000; ++i)
    {
        shared_counter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main()
{

    NBTlog log;
    log.start();
    for (int j = 0; j < 50; ++j)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i)
        {
            threads.emplace_back(worker, i);
        }

        for (auto& t : threads)
        {
            t.join();
        }
    }
    log.log("fetchadd");

    std::cout << shared_counter.load() << std::endl;
    return 0;
}
