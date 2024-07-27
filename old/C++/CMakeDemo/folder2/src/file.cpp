#include <boost/regex.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#include <iostream>

namespace demo {

// Simple class to be serialized
class Employee {
public:
    std::string name;
    int age;

    Employee() : name(""), age(0) {}

    Employee(std::string name, int age) : name(name), age(age) {}

private:
    // Serialization function
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & name;
        ar & age;
    }
};

// Function to serialize an Employee object
std::string serialize_employee(const Employee& emp) {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << emp;
    return archive_stream.str();
}

// Function to deserialize an Employee object
Employee deserialize_employee(const std::string& input) {
    std::istringstream archive_stream(input);
    boost::archive::text_iarchive archive(archive_stream);
    Employee emp;
    archive >> emp;
    return emp;
}

// Function to validate text against a given regex pattern
bool validate_text(const std::string& text, const std::string& pattern) {
    boost::regex expr(pattern);
    return boost::regex_match(text, expr);
}

} // namespace demo
