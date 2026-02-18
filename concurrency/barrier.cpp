#include <barrier>
#include <functional>
#include <iostream>
#include <stop_source>
#include <thread>

unsigned const num_threads = 10;
void finish_task();

std::barrier<std::function<void()>> b(num_threads, finish_task);

void worker(std::stop_token st, unsigned i)
{
    while (!st.stop_requested())
    {
        std::cout << i << '\n';
        b.arrive_and_wait();
    }
}
