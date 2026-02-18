#include <atomic>
#include <iostream>
#include <thread>

int counter = 0;
static const int LOOPS = 1e7;

void mythread(const char* arg)
{
    std::cout << arg << ": begin" << std::endl;
    for (int i = 0; i < LOOPS; ++i)
    {
        ++counter;
    }

    std::cout << arg << ": done" << std::endl;
}

int main()
{
    std::cout << "main: begin (counter = " << counter << ")" << std::endl;

    std::thread t1(mythread, "A");
    std::thread t2(mythread, "B");

    t1.join();
    t2.join();

    std::cout << "main: done with (counter = " << counter << ", goal " << 2 * LOOPS << ")"
              << std::endl;

    return 0;
}
