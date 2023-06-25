#include <iostream>
#include "cpp20.hpp"


import cpp20_module;

int main() {
    // Concepts
    cpp20::printEvenNumber(4);
    cpp20::printEvenNumber(7);

    // Modules
    moduleDemo();

    // Templated lambda function
    cpp20::performOperation(10);
    //cpp20::performOperation(3.14); // Not allowed: double does not match the IntegralNumber concept

    // Spaceship operator
    cpp20::MyClass obj1(5, 10);
    cpp20::MyClass obj2(10, -2);

    std::strong_ordering result = obj1 <=> obj2;

    if (result == std::strong_ordering::less) std::cout << "\nobj1 is less than obj2\n\n";
    else if (result == std::strong_ordering::greater) std::cout << "\nobj1 is greater than obj2\n\n";
    else std::cout << "\nobj1 and obj2 are equal\n\n";

    // no_unique_address as used with tag erasure
    cpp20::Person person{ "John Doe", 30 };
    cpp20::Device device{ 40, 8192, "Radeon RX 5700 XT" };

    cpp20::ErasedObject person_obj(person);
    cpp20::ErasedObject device_obj(device);

    // different print() function is called based on the struct
    person_obj.print();
    std::cout << "\n";
    device_obj.print();
    std::cout << "\n\n";

    // Coroutine example
    cpp20::CountCoroutine coroutine = cpp20::countTo(5);
    while (coroutine.move_next()) {
        std::cout << "Current number: " << coroutine.current() << std::endl;
    }


    return 0;
}