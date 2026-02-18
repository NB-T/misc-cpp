#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

static std::mutex mtx;
static int shared_counter = 0;

void worker(int thread_id)
{
    for (int i = 0; i < 1000; ++i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        ++shared_counter;
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(4);
    for (int i = 0; i < 4; ++i)
    {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << shared_counter << std::endl;
    return 0;
}
