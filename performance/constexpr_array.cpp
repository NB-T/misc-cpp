#include <cmath>
#include <iostream>

namespace detail
{
    double constexpr sqrtNewtonRaphson(double x, double curr, double prev)
    {
        return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
    }

    double constexpr sqrt(double x)
    {
        return x >= 0 && x < std::numeric_limits<double>::infinity()
                   ? sqrtNewtonRaphson(x, x, 0)
                   : std::numeric_limits<double>::quiet_NaN();
    }
} // namespace detail

struct Precalc
{
    double isqrt[1000];
    constexpr Precalc() : isqrt{}
    {
        for (int i = 0; i < 1000; ++i)
        {
            isqrt[i] = detail::sqrt(i);
        }
    }
};

int main()
{
    constexpr Precalc P;
    static_assert(P.isqrt[36] == 6);
    for (int i = 0; i < 1000; ++i)
    {
        std::cout << P.isqrt[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
