#include <iostream>
#include <vector>

class C
{
   public:
    int arr[16];
};

int main()
{
    std::vector<C> v(4);
    for (int i = 0; i < 4; ++i)
    {
        C c;
        for (int j = 0; j < 16; ++j)
        {
            c.arr[j] = j;
        }

        v[i] = c;
    }

    for (const auto& c : v)
    {
        for (int i = 0; i < 16; ++i)
        {
            std::cout << c.arr[i] << ' ';
        }
        std::cout << '\n';
    }

    {
        std::vector<C> w(v);
    }
    std::cout << "\n\n";

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << i << '\t';
        for (int j = 0; j < 16; ++j)
        {
            std::cout << v[i].arr[j] << ' ';
        }
        std::cout << '\n';
    }

    return EXIT_SUCCESS;
}
