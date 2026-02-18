#include "../nbtlog/include/nbtlog/NBTlog.hpp"
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

class Spinlock
{
  private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;

  public:
    void lock()
    {
        while (locked.test_and_set(std::memory_order_acquire))
        {
        }
    }

    void unlock()
    {
        locked.clear(std::memory_order_release);
    }
};

static Spinlock spinlock;
static int shared_counter = 0;

void worker(int thread_id)
{
    for (int i = 0; i < 1000; ++i)
    {
        spinlock.lock();
        ++shared_counter;
        spinlock.unlock();
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
    log.log("spinlock");

    std::cout << shared_counter << std::endl;
    return 0;
}
