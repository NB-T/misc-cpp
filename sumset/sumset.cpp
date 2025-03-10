/*
 * First
 * Map each member of the power set to its sumset
 */

#include <functional>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

template <int Modulus>
struct Hash;

template <int Modulus>
class Int
{
   public:
    // constructor
    constexpr Int(int _v) : v(_v % Modulus) {}

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

    // value accessor
    constexpr int value() const
    {
        return v;
    }

    constexpr Int& operator=(int other)
    {
        v = other % Modulus;
        return *this;
    }

    constexpr bool operator==(const Int<Modulus>& other) const
    {
        return v == other.v;
    }

    constexpr bool operator==(int other) const
    {
        return v == other % Modulus;
    }

    constexpr friend bool operator==(int other, const Int<Modulus>& i)
    {
        return i.v == other % Modulus;
    }

    constexpr bool operator!=(int other) const
    {
        return v != other % Modulus;
    }

    constexpr bool operator!=(const Int<Modulus>& other) const
    {
        return v != other.v;
    }

    constexpr friend bool operator!=(int other, const Int<Modulus>& i)
    {
        return i.v != other % Modulus;
    }

    friend std::ostream& operator<<(std::ostream& os, const Int<Modulus>& i)
    {
        os << i.v;
        return os;
    }

    friend struct Hash<Modulus>;

   private:
    int v;
};

template <int Modulus>
struct Hash
{
    std::size_t operator()(const Int<Modulus>& i) const
    {
        return std::hash<int>{}(i.v);
    }
};

template <int Modulus>
bool operator==(const std::unordered_set<Int<Modulus>, Hash<Modulus>>& s1, const std::unordered_set<int> s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }
    for (auto i : s1)
    {
        if (s2.count(i.value()) == 0)
        {
            return false;
        }
    }

    for (auto i : s2)
    {
        if (s1.count(Int<Modulus>(i)) == 0)
        {
            return false;
        }
    }

    return true;
}

template <int Modulus>
void test_addition(Int<Modulus> i1, Int<Modulus> i2, int expected)
{
    auto result = i1 + i2;
    if (result == expected)
    {
        std::cout << i1 << " + " << i2 << " = " << result << " (expected " << expected << ")"
                  << "\033[1;32m PASS \033[0m" << std::endl;
    }
    else
    {
        std::cout << i1 << " + " << i2 << " = " << result << " (expected " << expected << ")"
                  << "\033[1;31m FAIL \033[0m" << std::endl;
    }
}

template <int... Moduli>
void run_addition_tests(std::integer_sequence<int, Moduli...>)
{
    std::cout << "Running addition tests" << std::endl;

    // define some pairs to test, plus their expected sums
    ([&]()
     {
   	std::vector<std::pair<Int<Moduli>, Int<Moduli>>> tests = {
        {Int<Moduli>(0), Int<Moduli>(0)},
        {Int<Moduli>(0), Int<Moduli>(1)},
        {Int<Moduli>(1), Int<Moduli>(0)},
        {Int<Moduli>(1), Int<Moduli>(1)},
        {Int<Moduli>(1), Int<Moduli>(2)},
        {Int<Moduli>(1), Int<Moduli>(3)},
        {Int<Moduli>(1), Int<Moduli>(4)},
        {Int<Moduli>(1), Int<Moduli>(5)},
        {Int<Moduli>(1), Int<Moduli>(6)},
        {Int<Moduli>(1), Int<Moduli>(Moduli - 1)},
        {Int<Moduli>(1), Int<Moduli>(Moduli)}};

    for (auto test : tests)

    {
        test_addition(test.first, test.second, (test.first.value() + test.second.value()) % Moduli);
    } }(),
     ...);
    std::cout << std::endl;
}

template <int Modulus>
std::unordered_set<Int<Modulus>, Hash<Modulus>> sumset(const std::unordered_set<Int<Modulus>, Hash<Modulus>>& s1, const std::unordered_set<Int<Modulus>, Hash<Modulus>>& s2)
{
    std::unordered_set<Int<Modulus>, Hash<Modulus>> result;
    for (auto i : s1)
    {
        for (auto j : s2)
        {
            if (i != j)
            {
                result.insert(i + j);
            }
        }
    }
    return result;
}

template <int Modulus>
void test_sumset(const std::unordered_set<Int<Modulus>, Hash<Modulus>>& s1, const std::unordered_set<Int<Modulus>, Hash<Modulus>>& s2, const std::unordered_set<int>& expected)
{
    std::cout << "Sumset of { ";
    for (auto i : s1)
    {
        std::cout << i << " ";
    }
    std::cout << "} and { ";
    for (auto i : s2)
    {
        std::cout << i << " ";
    }
    std::cout << "} is { ";
    auto result = sumset(s1, s2);
    for (auto i : result)
    {
        std::cout << i << " ";
    }
    std::cout << "}"
              << " --- Expected { ";
    for (auto i : expected)
    {
        std::cout << i << " ";
    }
    std::cout << "}";
    if (result == expected)
    {
        std::cout << "\033[1;32m PASS \033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;31m FAIL \033[0m" << std::endl;
    }
}

/*
template <int... Moduli>
void run_sumset_tests(std::integer_sequence<int, Moduli...>)
{
    std::cout << "Running sumset tests" << std::endl;

    ([&]()
     {
         std::vector<std::pair<std::unordered_set<Int<Moduli>, Hash<Moduli>>, std::unordered_set<int>>> tests = {
             {{Int<Moduli>(1), Int<Moduli>(2),Int<Moduli>(3), Int<Moduli>(4)}, {0, 3, 4, 5, 6}}};

         for (auto test : tests)
         {
             test_sumset(test.first, test.first, test.second);
         } }(),
     ...);
}
*/

void run_sumset_tests()
{
    std::cout << "Running sumset tests" << std::endl;

    std::unordered_set<Int<7>, Hash<7>> s1 = {Int<7>(1), Int<7>(2), Int<7>(3), Int<7>(4)};
    std::unordered_set<int> expected = {0, 3, 4, 5, 6};

    test_sumset(s1, s1, expected);
}

int main()
{
    run_addition_tests(std::integer_sequence<int, 6, 7>{});

    run_sumset_tests();

    return EXIT_SUCCESS;
}
