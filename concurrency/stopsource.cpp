#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

void tf1(unsigned int id, std::atomic<bool>& terminated)
{
    std::srand(id);
    while (!terminated)
    {
        int r = std::rand() % 100;
        if (r == 0)
        {
            std::cerr << "Thread " << id << ": an error occurred." << std::endl;
            terminated = true;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void tf2(std::stop_token stoken, unsigned int id, std::stop_source source)
{
    std::srand(id);
    while (!stoken.stop_requested())
    {
        int r = std::rand() % 100;
        if (r == 0)
        {
            std::cerr << "Thread " << id << ": an error occurred." << std::endl;
            source.request_stop();
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::atomic<bool> terminated = false;
    // std::thread t1(&tf1, 1, std::ref(terminated));
    // std::thread t2(&tf1, 2, std::ref(terminated));
    // won't work --- std::thread requires args package to have a value field
    // but std::atomic<T> doesn't automatically convert to a type with such a field (apparently?)
    // ---edit---
    // maybe something about thread-local storage?
    // like Callable and args are copied to thread-local storage by default
    // so need to super-force referenceness (whatever the heck that means)
    std::thread t1(&tf1, 1, terminated);
    std::thread t2(&tf1, 2, terminated);

    std::stop_source source;
    std::stop_token stoken = source.get_token();

    // std::thread t1(&tf2, stoken, 1, source);
    // std::thread t2(&tf2, stoken, 2, source);

    t1.join();
    t2.join();
    std::cerr << "Both threads finished." << std::endl;
    int k;
    std::cin >> k;

    return EXIT_SUCCESS;
}
