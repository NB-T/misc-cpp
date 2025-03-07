/*
 * First
 * Map each member of the power set to its sumset
 */

#include <iostream>
#include <unordered_set>
#include <utility>

template <int Modulus>
class Int
{
   public:
    // constructor
    constexpr Int(int _v)
    {
        v = _v % Modulus;
    }

    constexpr Int operator+(Int<Modulus> other)
    {
        return static_cast<Int<Modulus>>((v + other.v) % Modulus);
    }

    constexpr Int& operator=(const Int<Modulus>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        v = other.v;
        return *this;
    }

    constexpr Int& operator=(int& other)
    {
        v = other % Modulus;
        return *this;
    }

    constexpr bool operator==(const Int<Modulus>& other) const
    {
        return v == other.v;
    }

    friend std::ostream& operator<<(std::ostream& os, const Int<Modulus>& i)
    {
        os << i.v;
        return os;
    }

   private:
    int v;
};

template <int Modulus>
void test_adddition(Int<Modulus> i1, Int<Modulus> i2)
{
    std::cout << i1 << " + " << i2 << " = " << i1 + i2 << " (mod " << Modulus << ")" << std::endl;
}

template <int... Modulus>
void run_tests(std::integer_sequence<int, Modulus...>)
{
    (test_adddition(Int<Modulus>(3), Int<Modulus>(4)), ...);
    (test_adddition(Int<Modulus>(3), Int<Modulus>(5)), ...);
    (test_adddition(Int<Modulus>(3), Int<Modulus>(6)), ...);
}

int main()
{
    run_tests(std::integer_sequence<int, 6, 7>{});

    return EXIT_SUCCESS;
}
