/*
 * First
 * Map each member of the power set to its sumset
 */

#include <iostream>
#include <unordered_set>

template <int Modulus>
class Int
{
   public:
    // constructor
    Int(int _v)
    {
        v = _v % Modulus;
    }
    Int operator+(Int<Modulus> other)
    {
        return static_cast<Int<Modulus>>((v + other.v) % Modulus);
    }

    Int& operator=(const Int<Modulus>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        v = other.v;
        return *this;
    }

    Int& operator=(int& other)
    {
        v = other % Modulus;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Int<Modulus>& i)
    {
        os << i.v;
        return os;
    }

   private:
    int v;
};

int main()
{
    Int<4> i1 = 3;
    Int<4> i2 = 1;

    std::cout << i1 + i2 << std::endl;
    return EXIT_SUCCESS;
}
