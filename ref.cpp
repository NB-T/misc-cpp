#include <functional>
#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
void foo(T x)
{
    auto r = std::ref(x);
    std::cout << std::boolalpha << std::is_same<T&, decltype(r)>::value << std::endl;
    std::cout << "x : " << typeid(x).name() << '\t' << "std::ref(x) : " << typeid(r).name() << std::endl;
    std::cout << std::is_same<T&, decltype(r.get())>::value << std::endl;
    std::cout << "x : " << typeid(x).name() << '\t' << "std::reference_wrapper.get() : " << typeid(r.get()).name() << std::endl;
}

int main()
{
    int x = 5;
    foo(x);
    return EXIT_SUCCESS;
}
