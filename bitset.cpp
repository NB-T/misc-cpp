#include <bitset>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {0, 1, 1, 0, 1, 0, 1, 1};
    std::vector<std::bitset<2>> vbs = {0b10, 0b01, 0b01, 0b11};
    std::vector<bool> vb = {true, false, true, false, true, false, true, true};

    // print how many bytes v, vbs, and vb use
    std::cout << "v uses " << v.size() * sizeof(int) << " bytes\n";
    std::cout << "vbs uses " << vbs.size() * sizeof(std::bitset<2>) << " bytes\n";
    std::cout << "vb uses " << vb.size() * sizeof(bool) << " bytes\n";

    std::vector<int> v1(1000, 1);
    std::vector<std::bitset<2>> vbs1(1000, 0b11);

    // print how many bytes v1 and vbs1 use
    std::cout << "v1 uses " << v1.size() * sizeof(int) << " bytes\n";
    std::cout << "vbs1 uses " << vbs1.size() * sizeof(std::bitset<2>) << " bytes\n";

    std::bitset<1> b1 = 1;
    std::bitset<2> b2 = 2;
    std::bitset<3> b3 = 3;
    std::bitset<4> b4 = 4;

    // print how many bytes b1, b2, b3, and b4 use
    std::cout << "b1 uses " << sizeof(b1) << " bytes\n";
    std::cout << "b2 uses " << sizeof(b2) << " bytes\n";
    std::cout << "b3 uses " << sizeof(b3) << " bytes\n";
    std::cout << "b4 uses " << sizeof(b4) << " bytes\n";

    return EXIT_SUCCESS;
}
