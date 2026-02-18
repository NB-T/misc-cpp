#include <iostream>
#include <thread>

void mythread(const char* arg)
{
    std::cout << arg << std::endl;
}

int main()
{
    std::cout << "main: begin" << std::endl;

    std::thread t1(mythread, "A");
    std::thread t2(mythread, "B");

    t1.join();
    t2.join();

    std::cout << "main: end" << std::endl;

    return 0;
}
