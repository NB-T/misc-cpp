#include <iostream>

struct NumericalFunctions
{
    void scale(this auto&& self, double multiplicator)
    {
        self.setValue(self.getValue() * multiplicator);
    }
};

struct Sensitivity : public NumericalFunctions
{
    Sensitivity(double v) : value(v) {}
    double getValue() const { return value; }
    void setValue(double v) { value = v; }
    double value;
};

int main()
{
    Sensitivity s{1.2};
    s.scale(2.0);

    std::cout << "s.getValue() = " << s.getValue() << std::endl;

    return EXIT_SUCCESS;
}
