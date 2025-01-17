#include <concepts>
#include <iostream>

class AnimalTag
{
};

template <typename T>
concept Animal = requires(T animal)
{
    animal.make_sound();
}
&&std::derived_from<T, AnimalTag>;

template <Animal T>
void print(T const& animal)
{
    animal.make_sound();
}

class Sheep : public AnimalTag
{
   public:
    void make_sound() const { std::cout << "baa" << std::endl; }
};

int main()
{
    Sheep sheep;
    print(sheep);
}
