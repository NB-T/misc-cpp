#include "../nbtlog/include/nbtlog/NBTlog.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex print_mutex;

void worker(int id, bool use_lock)
{
    if (use_lock)
    {
        std::scoped_lock lock(print_mutex);
        std::cout << "Worker " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Worker " << id << " done" << std::endl;
    }

    else
    {
        std::cout << "Worker " << id << std::endl;
