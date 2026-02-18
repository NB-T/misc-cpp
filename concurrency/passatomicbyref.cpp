#include <atomic>
#include <iostream>
#include <thread>

void f(std::atomic<int>& i)
{
    std::cout << i << std::endl;
}

int main()
{
    std::atomic<int> i = 1;

    // these both work
    f(i);
    f(std::ref(i));

    return EXIT_SUCCESS;
}
