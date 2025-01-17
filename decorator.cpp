#include <array>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory_resource>
#include <vector>

int main()
{
    std::array<std::byte, 1000> raw;
    std::pmr::monotonic_buffer_resource buffer{raw.data(), raw.size(), std::pmr::null_memory_resource()};
    std::pmr::vector<std::pmr::string> strings{&buffer};
    strings.emplace_back("String longer than what SSO can handle");
    strings.emplace_back("Another string beyond SSO");
    strings.emplace_back("Yet another string beyond SSO");

    for (const auto& s : strings)
    {
        std::cout << std::quoted(s) << '\n';
    }

    return 0;
}
