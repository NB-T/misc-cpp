#include <iostream>
#include <type_traits>

int main()
{
    using two_t = std::integral_constant<int, 2>;
    using four_t = std::integral_constant<int, 4>;

    static_assert(not std::is_same_v<two_t, four_t>);
    static_assert(two_t::value * 2 == four_t::value, "2 * 2 != 4");
    static_assert(two_t() << 1 == four_t() >> 0, "2 * 2 != 4");

    enum class E
    {
        e1,
        e2
    };

    using c1 = std::integral_constant<E, E::e1>;
    using c2 = std::integral_constant<E, E::e2>;

    static_assert(c1::value != E::e2);
    static_assert(c1() == E::e1);
    static_assert(std::is_same_v<c2, c2>);

    return EXIT_SUCCESS;
}
