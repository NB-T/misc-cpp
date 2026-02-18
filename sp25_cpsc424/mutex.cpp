#include "../nbtlog/include/nbtlog/NBTlog.hpp"
#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::mutex m;

void inc()
{
    for (int i = 0; i < 1000; ++i)
    {
        std::lock_guard<std::mutex> lock(m);
        ++counter;
    }
}

int main()
{
    NBTlog log;
    log.start();

    for (int j = 0; j < 50; ++j)
    {
        std::thread t1(inc);
        std::thread t2(inc);
        std::thread t3(inc);
        std::thread t4(inc);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

    log.log("mutex");
    std::cout << "Final counter: " << counter << std::endl;

    return 0;
}
