#include <array>
#include <iostream>

class valueChanger {
private:
    int value{};
public:
    valueChanger(int val) : value{ val } {}

    valueChanger(valueChanger& other) : value{ other.getValue() } {}

    int getValue() const { return value; }

    // Assignment operator
    // why const?
    const valueChanger& operator=(const valueChanger& other) {
        // Prevent self assignment
        if (&other != this) value = other.getValue();
        return *this;
    }

    // Equality operator
    bool operator==(const valueChanger& other) const {
        if (value == other.getValue()) return true;
        return false;
    }

    // Free inequality operator
    bool operator!=(const valueChanger& other) const {
        return (*this == other);
    }
};

class arrayHolder {
private:
    std::array<int, 10> data{};
public:
    arrayHolder() {}

    std::array<int, 10> getDat() const { return data; }

    // subscript (non-const objects) -> get modifiable lvalue
    int& operator[](int index) {
        return data[index];
    }

    // subscript (const objects) -> get rvalue
    int operator[](int index) const {
        return data[index];
    }

    // Overloaded cast operators
    // Convert custom objects into fundamental types or other custom types e.g. static_cast<T>
    // MUST be non-static member function
    operator std::string() const {

    }

    // Leftmost/only operand MUST BE AN OBJECT/REF TO OBJECT OF THIS CLASS if operator function is a member function
};
// Leftmost/only operand can be any other object/type if operator function is not a member function
// i.e. friend functions
std::ostream& operator<<(std::ostream& os, const arrayHolder& aH) {

}

std::ostream& operator<<(std::ostream& os, const arrayHolder& aH) {

}
