#include <iostream>
#include <latch>
#include <optional>
#include <thread>
#include <vector>

int main()
{
    unsigned const thread_count = 10;
    std::latch done(thread_count);
    std::vector<std::optional<int>> data(thread_count);
    std::vector<std::jthread> threads;
    for (unsigned int i = 0; i < thread_count; ++i)
    {
        threads.push_back(std::jthread([&, i]
                                       {
					data[i] = i;
					done.count_down();
					++*(data[i]); }));
    }
    done.wait();
    for (auto i : data)
    {
        if (i.has_value())
        {
            std::cout << i.value() << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
