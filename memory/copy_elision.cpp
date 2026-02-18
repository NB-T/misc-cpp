#include <iostream>

struct C
{
    C() = default;
    C(const C&)
    {
        std::cout << "Copying\n";
    }
};

C f()
{
    return C();
}

struct Data
{
    char bytes[16];
};

Data F()
{
    Data result = {};
    return result;
}

int main()
{
    // std::cout << "Hello\n";
    // C obj = f();

    Data d = F();
}

// or equivalently
/*
Data* F_star(Data* _hiddenAddress)
{
    Data result = {};
    *_hiddenAddress = result;
    return _hiddenAddress;
}

int main()
{
        Data _hidden;
        Data d = *F(&_hidden);
                }
*/
