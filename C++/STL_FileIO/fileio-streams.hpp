#ifndef FILEIO_STREAMS_HPP
#define FILEIO_STREAMS_HPP

/* Includes */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <filesystem>
#include <functional>
#include <regex>

/* Defines */
using string = std::string;

namespace stringHelper {
    bool checkIfNumberContainsE(const std::string& number) {
        std::string str = "";

        return (number.find('e') != std::string::npos || number.find('E') != std::string::npos);
    }

    bool checkIfNumberContainsDot(const std::string& number) {
        return (number.find('.') != std::string::npos);
    }

    int numCharsBeforeE(const std::string& number) {
        size_t posE = number.find('e');
        if (posE == std::string::npos)
            posE = number.find('E');
        if (posE != std::string::npos)
            return static_cast<int>(posE);
        return static_cast<int>(number.size());
    }

    bool isNumeric(const std::string& str) {
        // Regular expression pattern for numeric values
        std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");
        return std::regex_match(str, pattern);
    }

    //Issues with this one
    int expToInteger(const std::string& number) {
        size_t posE = number.find('e');
        if (posE == std::string::npos)
            posE = number.find('E');
        if (posE != std::string::npos) {
            std::string exponent = number.substr(posE + 1);
            if (exponent[0] == '+' || exponent[0] == '-')
                exponent = exponent.substr(1);  // Ignore the sign
            return std::stoi(exponent);
        }
        return 0;
    }

    template <typename T>
    int getMaxDigits() {
        std::string minValue = std::to_string(std::numeric_limits<T>::min());
        std::string maxValue = std::to_string(std::numeric_limits<T>::max());

        int minLength = minValue.size();
        if (minValue.find('e') != std::string::npos || minValue.find('E') != std::string::npos) {
            size_t posE = minValue.find('e');
            if (posE == std::string::npos)
                posE = minValue.find('E');
            if (posE != std::string::npos) {
                std::string exponent = minValue.substr(posE + 1);
                int expValue = std::stoi(exponent);
                minLength += std::to_string(expValue).size();
            }
        }

        int maxLength = maxValue.size();
        if (maxValue.find('e') != std::string::npos || maxValue.find('E') != std::string::npos) {
            size_t posE = maxValue.find('e');
            if (posE == std::string::npos)
                posE = maxValue.find('E');
            if (posE != std::string::npos) {
                std::string exponent = maxValue.substr(posE + 1);
                int expValue = std::stoi(exponent);
                maxLength += std::to_string(expValue).size();
            }
        }

        return std::max(minLength, maxLength);
    }
}

namespace fileio {
   
    //C++ views files as a sequence of bytes.
    //End denoted with EOF marker or at a specific byte recorded in an OS-maintained administrative data structure
    struct NumberVectors {
        std::vector<int> ints;
        std::vector<float> floats;
        std::vector<double> doubles;
        std::vector<long> longs;
    };

    //Helper functions for process_file()
    void printVector(std::ofstream& outputFile, const NumberVectors& separatedNumbers) {
        int count = 0;
        outputFile << "Ints (" << separatedNumbers.ints.size() << ")\n----------------\n";
        for (const auto& num : separatedNumbers.ints) {
            outputFile << num << "\n";
            count++;
        }

        outputFile << "\nFloats (" << separatedNumbers.floats.size() << ")\n----------------\n";
        for (const auto& num : separatedNumbers.floats) {
            outputFile << num << "\n";
            count++;
        }

        outputFile << "\nDoubles (" << separatedNumbers.doubles.size() << ")\n----------------\n";
        for (const auto& num : separatedNumbers.doubles) {
            outputFile << num << "\n";
            count++;
        }

        outputFile << "\nLongs (" << separatedNumbers.longs.size() << ")\n----------------\n";
        for (const auto& num : separatedNumbers.longs) {
            outputFile << num << "\n";
            count++;
        }

        outputFile << "Total numbers found: " << count << "\n\n";
    }

    template<typename T, typename U, typename V, typename W>
    void process_file() {
        namespace fs = std::filesystem;

        std::string filename;
        std::cout << "Enter the file name: ";
        std::getline(std::cin, filename);

        // Check if the file exists
        while (!fs::exists(filename)) {
            std::cerr << "File not found. Please enter a valid file name: ";
            std::getline(std::cin, filename);
        }

        std::ifstream inputFile(filename);
        if (!inputFile) {
            std::cerr << "Failed to open the file: " << filename << std::endl;
            return;
        }

        std::string line;
        NumberVectors separatedNumbers;

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string number;
            while (iss >> number) {
                // Skip non-numeric entries
                if (stringHelper::isNumeric(number)) {
                    continue;
                }


                bool isInt = false;
                bool isLong = false;
                bool isFloat = false;
                bool isDouble = false;

                int currentLength = static_cast<int>(number.size());

                bool containsE = stringHelper::checkIfNumberContainsE(number);
                bool containsDot = stringHelper::checkIfNumberContainsDot(number);

                if (containsDot && containsE) {
                    currentLength += stringHelper::numCharsBeforeE(number) - 1;
                    std::string exp = number.substr(stringHelper::numCharsBeforeE(number), std::string::npos);
                    currentLength += stringHelper::expToInteger(exp);
                }
                else if (containsDot && !containsE) {
                    currentLength += static_cast<int>(number.size()) - 1;
                }
                else if (!containsDot && containsE) {
                    currentLength += stringHelper::numCharsBeforeE(number);
                    std::string exp = number.substr(stringHelper::numCharsBeforeE(number), std::string::npos);
                    currentLength += stringHelper::expToInteger(exp);
                }

                if (!containsDot) {
                    if (currentLength < stringHelper::getMaxDigits<int>()) {
                        isInt = true;
                    }
                    else {
                        isLong = true;
                    }
                }
                else {
                    if (currentLength < stringHelper::getMaxDigits<float>()) {
                        isFloat = true;
                    }
                    else {
                        isDouble = true;
                    }
                }

                if (isInt) {
                    try {
                        separatedNumbers.ints.push_back(std::stoi(number));
                    }
                    catch (...) {
                        // Failed to convert to int
                    }
                }
                else if (isLong) {
                    try {
                        separatedNumbers.longs.push_back(std::stoll(number));
                    }
                    catch (...) {
                        // Failed to convert to long
                    }
                }
                else if (isFloat) {
                    try {
                        separatedNumbers.floats.push_back(std::stof(number));
                    }
                    catch (...) {
                        // Failed to convert to float
                    }
                }
                else if (isDouble) {
                    try {
                        separatedNumbers.doubles.push_back(std::stod(number));
                    }
                    catch (...) {
                        // Failed to convert to double
                        try {
                            separatedNumbers.doubles.push_back(std::stold(number));  // Attempt to convert as long double
                        }
                        catch (...) {
                            // Failed to convert to double or long double
                        }
                    }
                }
            }
        }

        std::string outputFilename;
        std::cout << "Enter the output file name: ";
        std::getline(std::cin, outputFilename);

        std::ofstream outputFile(outputFilename);
        if (!outputFile) {
            std::cerr << "Failed to open the output file: " << outputFilename << std::endl;
            return;
        }

        printVector(outputFile, separatedNumbers);
    }

    string read_file_to_string(const string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    string read_file_to_string(const string& directory, const string& filename) {
        string filePath;
        //Verify that directory to search ends in a /, add it if not
        if (directory.at(directory.length() - 1) != '/') {
            filePath = directory + "/" + filename;
        }
        else filePath = directory + filename;

        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }



}

namespace streamio {
    void print_address() {
        //icky
        const char* const word{ "Scam" };

        //std::cout will show word like a string rather than a memory address
        std::cout << "std::cout << string: " << word << std::endl;
        std::cout << "std::cout << static_cast<const void*>(string): " << static_cast<const void*>(word) << "\n\n";
    }

    void stream_extraction_as_condition() {
        int number;
        std::cout << "Enter a positive number (0 to exit): ";

        while (std::cin >> number && number != 0) {
            // Process the input number
            std::cout << "You entered: " << number << std::endl;

            // Prompt for the next number
            std::cout << "Enter any number (0 to escape): ";
        }
        std::cout << "Exiting function..." << "\n\n";
    }

    void getLine_get_put() {
        std::string line;
        char ch;

        std::cout << "Enter a sentence: ";
        std::getline(std::cin, line); // Read a line of input

        std::cout << "Outputting characters using get(): ";
        for (std::size_t i = 0; i < line.length(); ++i) {
            std::cin.get(ch);
            std::cout.put(ch);
        }
        std::cout << std::endl;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining newline character

        std::cout << "Enter another sentence: ";
        std::getline(std::cin, line); // Read another line of input

        std::cout << "Outputting characters using getline() and eof(): ";
        std::istringstream iss(line);
        while (std::getline(iss, line)) {
            std::cout << line << std::endl;
            if (iss.eof()) {
                std::cout << "End of file reached." << "\n\n";
                break;
            }
        }
    }

    void peek_putback_ignore() {
        std::string sentence;
        std::cout << "Enter a sentence: ";
        std::getline(std::cin, sentence);

        std::istringstream input(sentence);

        char ch;
        std::string word;

        // Skip leading whitespace
        while (std::isspace(input.peek())) {
            input.ignore();
        }

        // Read and process characters until encountering a space
        while (input.get(ch) && ch != ' ') {
            // Process the character
            std::cout << "Processing character: " << ch << std::endl;
        }

        // Read and process a word
        input >> word;

        // Save position after reading the word
        std::streampos afterWord = input.tellg();

        if (word.empty()) {
            std::cout << "Failed to extract word from input." << std::endl;
        }
        else {
            std::cout << "Word: " << word << std::endl;
        }

        // Set position to beginning of the word
        input.seekg(afterWord);

        // Read and process the character again
        if (input.get(ch)) { // check if get is successful
            std::cout << "Character after putback: " << ch << "\n\n";
        }
    }

    void demonstrate_formatting() {
        double pi = 3.14159265358979323846;
        double sqrt2 = 1.41421356237309504880;

        std::cout << std::setprecision(5) << "Default precision: " << pi << std::endl;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Fixed-point precision: " << pi << std::endl;

        std::cout << std::scientific << std::setprecision(3);
        std::cout << "Scientific notation precision: " << sqrt2 << std::endl;

        int value = 123;
        std::cout << "setw example: " << std::setw(8) << value << "\n\n";
    }

    void demonstrate_formatting_string() {
        auto formatNumber = [](double number, int precision, int width) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(precision) << std::setw(width) << number;
            return oss.str();
        };

        double pi = 3.14159265358979323846;
        double sqrt2 = 1.41421356237309504880;

        std::string formattedPi = formatNumber(pi, 5, 10);
        std::string formattedSqrt2 = formatNumber(sqrt2, 3, 8);

        std::cout << "Formatted Pi: " << formattedPi << std::endl;
        std::cout << "Formatted Sqrt(2): " << formattedSqrt2 << "\n\n";
    }

    void demonstrate_justification() {
        double number = 1234.56789;

        // Showpoint - Always show the decimal point and trailing zeros
        std::cout << "Number with showpoint: " << std::showpoint << number << std::endl;

        // Left-justified
        std::cout << std::left << std::setw(20) << "Left-justified:" << std::setw(10) << number << std::endl;

        // Right-justified
        std::cout << std::right << std::setw(20) << "Right-justified:" << std::setw(10) << number << std::endl;

        // Internal justification
        std::cout << std::internal << std::setw(20) << "Internal justification:" << std::setw(10) << number << "\n\n";
    }

    void demonstrate_showbase() {
        int numbers[] = { 0, 256, 512, 768, 1024 };

        std::cout << std::setw(10) << "Decimal" << std::setw(15) << "Hexadecimal" << std::setw(10) << "Octal" << std::endl;
        std::cout << std::setw(10) << std::setfill('-') << "" << "  " << std::setw(15) << std::setfill('-') << "" << "  " << std::setw(10) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

        for (int number : numbers) {
            std::cout << std::setw(10) << std::dec << std::showbase << number << "  ";
            std::cout << std::setw(15) << std::hex << std::showbase << number << "  ";
            std::cout << std::setw(10) << std::oct << std::showbase << number << std::endl;
        }


        std::cout << "\nBinary*:\n";
        for (int number : numbers) {
            std::cout << std::bitset<sizeof(number) * 8>(number) << std::endl;
        }

        std::cout << "\n*Note that showbase is not available for binary. You must use e.g. std::bitset<sizeof(number) * 8>(number)\n\n";
    }

    void demonstrate_representation() {
        struct Number {
            std::string title;
            double value;
        };

        Number numbers[] = {
            {"Avogadro constant:", 6.022141e23},
            {"Speed of light:", 299792458},
            {"Elementary charge:", 1.602177e-19}
        };

        std::cout << std::left;
        std::cout << std::setw(20) << " " << std::setw(20) << "Scientific" << std::setw(40) << "Fixed" << std::setw(20) << "Default" << std::endl;
        std::cout << std::setw(20) << std::setfill('-') << "" << std::setw(20) << std::setfill('-') << "" << std::setw(40) << std::setfill('-') << "" << std::setw(20) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

        for (const auto& number : numbers) {
            std::cout << std::setw(20) << std::left << number.title;
            std::cout << std::setw(20) << std::scientific << std::setprecision(6) << number.value;
            std::cout << std::setw(40) << std::fixed << std::setprecision(6) << number.value;
            std::cout << std::setw(20) << std::defaultfloat << std::setprecision(6) << number.value;
            std::cout << std::endl;
        }
        std::cout << "\n\n";
    }

    void demonstrate_boolalpha() {
        bool value = true;

        std::cout << "The boolean value is true. What if we print it out?\n";

        std::cout << "Default: " << value << std::endl;

        std::cout << std::boolalpha;
        std::cout << "With std::boolalpha: " << value << std::endl;

        std::cout << std::noboolalpha;
        std::cout << "With std::noboolalpha: " << value << "\n\n";
    }

    void demonstrate_flags() {
        int intValue;
        float floatValue;
        double doubleValue;

        std::cout << "Enter an integer value: ";
        std::cin >> intValue;

        std::cout << "Enter a float value: ";
        std::cin >> floatValue;

        std::cout << "Enter a double value: ";
        std::cin >> doubleValue;

        //Print default flags and values
        std::ios_base::fmtflags original_format{std::cout.flags()};
        std::cout << "\nDefault flags:" << std::endl;
        std::cout << "flags() = " << std::cout.flags() << std::endl;
        std::cout << "Integer value: " << intValue << std::endl;
        std::cout << "Float value: " << floatValue << std::endl;
        std::cout << "Double value: " << doubleValue << std::endl;

        //Change and display new flags
        std::cout << "\nNew flags:" << std::endl;
        std::cout.flags(std::ios::scientific | std::ios::uppercase);
        std::cout << "flags() = " << std::cout.flags() << std::endl;
        std::cout << "Updated Integer value: " << intValue << std::endl;
        std::cout << "Updated Float value: " << floatValue << std::endl;
        std::cout << "Updated Double value: " << doubleValue << std::endl;

        //Restore original flags and display
        std::cout << "\nRestored flags:" << std::endl;
        std::cout.flags(original_format);
        //Alternatively:
        //std::cout.flags(std::ios::dec);
        std::cout << "flags() = " << std::cout.flags() << std::endl;
        std::cout << "Original Integer value: " << intValue << std::endl;
        std::cout << "Original Float value: " << floatValue << std::endl;
        std::cout << "Original Double value: " << doubleValue << std::endl;
    }
}

#endif /* FILEIO_STREAMS_HPP */