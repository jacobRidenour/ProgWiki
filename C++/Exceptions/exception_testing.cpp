#include <iostream>
#include <stdexcept>
#include <string>

int getIntFromUser() {
    // Keep trying til we get a valid input from the user
    while (true) {
        try {
            std::cout << "Enter an integer: ";
            std::string input;
            std::cin >> input;

            // Attempt to convert the input string to an integer
            int num = std::stoi(input);

            // If the conversion succeeds, return the integer
            return num;
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input! Please enter an integer." << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cout << "Input out of range! Please enter a valid integer." << std::endl;
        }
    }
}

int main() {
    int num = getIntFromUser();
    std::cout << "You entered: " << num << std::endl;

    return 0;
}