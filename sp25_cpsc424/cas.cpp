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
        int old_val = shared_counter.load(std::memory_order_relaxed);
        int new_val = old_val + 1;

        while (!shared_counter.compare_exchange_weak(
            old_val,
            new_val,
            std::memory_order_release,
            std::memory_order_relaxed
        ))
        {
            old_val = shared_counter.load(std::memory_order_relaxed);
            new_val = old_val + 1;
        }
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
    log.log("cas");

    std::cout << shared_counter.load() << std::endl;
    return 0;
}
