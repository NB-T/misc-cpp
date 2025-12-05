#include <iostream>

struct T
{
    double a;
    double b;
};

int main()
{
    std::cout << sizeof(int) << std::endl;
    T thingy{4, 5};
    std::cout << sizeof(T) << std::endl;
    std::cout << sizeof thingy << std::endl;
    std::cout << thingy.a << ' ' << thingy.b << std::endl;
    T arr[3]{T(thingy), T(thingy), T(thingy)};
    T* ptr = arr;
    std::cout << ptr[0].a << std::endl;
    std::cout << ptr->a << std::endl;
    std::cout << (ptr + 1)->a << std::endl;
    std::cout << (ptr + 1) - ptr << std::endl;
    std::cout << arr[0].a << std::endl;
    return 0;
}
