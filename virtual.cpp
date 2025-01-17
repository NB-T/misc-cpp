#include <iostream>

class Animal
{
   public:
    virtual void eat()
    {
        std::cout << "I'm eating generic food.\n";
    }
};

void func(Animal* a)
{
    a->eat();
}

class Cat : public Animal
{
   public:
    void eat()
    {
        std::cout << "I'm eating a rat.\n";
    }
};

int main()
{
    Animal* animal = new Animal;
    Cat* cat = new Cat;

    func(animal);
    func(cat);

    return 0;
}
