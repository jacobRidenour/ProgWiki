#include <iostream>

class Base { public: virtual ~Base() {} };
class Derived : public Base { public: void derivedFunction() { std::cout << "Derived function called." << std::endl; } };

int main() {
    int x = 10;
    double y = static_cast<double>(x);
    /* Static Cast */
    // We could just do "double y = x" and the conversion would happen.
    // What's the point?
    // -> Safe & well-defined type conversions
    //    that can be checked at *compile-time*
    //    rather than runtime
    std::cout << "int x: " << x << "\n";
    std::cout << "x after static cast to a double: " << x << "\n\n";

    const int f = 20;
    const int* const_ptr = &f;
    int* mutable_ptr = const_cast<int*>(const_ptr);
    std::cout << "const int f: " << f << "\n";
    std::cout << "value of const int* f: " << *const_ptr << "\n";
    std::cout << "value of const int* f after const cast to int*: " << *const_ptr << "\n";
    //*const_ptr = 30;      //Not allowed, the pointer is const
    *mutable_ptr = 30;      //Allowed
    /* Const Cast */
    // Used to add or remove const, volatile, or const volatile qualifiers
    // Lets us modify the value pointed to by mutable_ptr and see the effect on the original value
    // Use with caution; only when you are certain the resulting pointer or reference will not
    // be used to modify a value that is originally declared as const
    std::cout << "updated value of int* originally assigned to f: " << *const_ptr << "\n";
    std::cout << "current value of const int f: " << f << "\n\n";

    int mol = 42;
    void* void_ptr_mol = reinterpret_cast<void*>(&mol);         //Convert int* -> void*
    int* int_ptr_mol = reinterpret_cast<int*>(void_ptr_mol);    //convert void* -> int*
    std::cout << "int mol: " << mol << "\n";
    std::cout << "value of void* to mol created with reinterpret_cast of &mol: " << void_ptr_mol << "\n";
    std::cout << "value of int* to mol created with reinterpret_cast of void* to mol: " << *int_ptr_mol << "\n\n";
    /* Reinterpret Cast */
    // Low-level reinterpretation of pointers or data types. Use sparingly.
    // Only use it when you need to perform reinterpretation between unrelated types,
    // like pointer -> integer conversions or other non-standard conversions
    // Be very careful to ensure type safety and avoid undefined behavior

    std::cout << "Casting and polymorphism" << "\n------------------------\n";
    Base* base_ptr = new Derived();
    std::cout << "base_ptr is a Base* but it has been initialized as a Derived object.\n";

    Derived* derived_ptr = static_cast<Derived*>(base_ptr);
    std::cout << "derived_ptr has been initialized as a static_cast of base_ptr (to Derived*).\n";
    std::cout << "Calling derived_ptr->derivedFunction()...\n\n";
    derived_ptr->derivedFunction();

    Derived* derived_ptr_2 = dynamic_cast<Derived*>(base_ptr);
    std::cout << "derived_ptr_2 has been initialized as a dynamic_cast of base_ptr (to Derived*).\n";
    std::cout << "Checking if the dynamic cast was successful by calling derived_ptr_2->derivedFunction()...\n";
    if (derived_ptr_2 != nullptr) derived_ptr->derivedFunction();
    else std::cout << "Dynamic cast failed.\n";
    /* Dynamic Cast */
    // Used for SAFE runtime type checking & downcasting in polymorphic hierarchies.
    // It ensures type safety and allows you to handle casting failures gracefully
    // by returning nullptr for pointers or throwing a std::bad_cast exception for references

    delete base_ptr;

    return 0;
}