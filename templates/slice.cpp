#include <iostream>
#include <span>
#include <vector>

template <int left = 0, int right = 0, typename T>
constexpr auto slice(T&& container)
{
    if constexpr (right > 0)
    {
        return std::span(begin(std::forward<T>(container)) + left, begin(std::forward<T>(container)) + right);
    }
    else
    {
        return std::span(begin(std::forward<T>(container)) + left, end(std::forward<T>(container)) + right);
    }
}

int main()
{
    std::vector v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto v0 = slice<1, 0>(v);
    for (auto i : v0)
    {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
    auto v1 = slice<0, -1>(v);
    for (auto i : v1)
    {
        std::cout << i << std::endl;
    }
}
