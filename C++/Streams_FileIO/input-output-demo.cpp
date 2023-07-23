#include <iostream>
#include "fileio-streams.hpp"

/* Using Declarations */
using string = std::string;

/* Function Declarations */
void stream_manip_demo();
void fileio_demo();

int main() {

    //Stream manipulation examples
    //stream_manip_demo();


    //FileIO examples
    fileio_demo();    

    return 0;
}

void stream_manip_demo() {
    //<< has been overloaded in cout. Demonstration
    streamio::print_address();

    //Stream extraction result as condition
    streamio::stream_extraction_as_condition();

    //Example of getLine(), get(), and put() in action
    streamio::getLine_get_put();

    //Example of peek(), putback(), and ignore() in action
    streamio::peek_putback_ignore();

    //Example of setw, setprecision
    streamio::demonstrate_formatting();

    //Example of setw, setprecision to create a string?
    streamio::demonstrate_formatting_string();

    //Example of showpoint and justification of output
    streamio::demonstrate_justification();

    //Example of showing the number variable in different bases
    streamio::demonstrate_showbase();

    //Example of scientific vs. fixed vs. default precision
    streamio::demonstrate_representation();

    //Example of boolapha for stream output
    streamio::demonstrate_boolalpha();

    //Example of cout flags
    streamio::demonstrate_flags();
}

void fileio_demo() {
    
    //Get name and DOB from the user and write it to a specified file
    //Makes use of lambda functions and the filesystem library
    //fileio::demonstrate_file_IO();
    
    //Read a file of random numbers of various type (int, double, etc.) as well as strings and special characters
    //Read only the numbers and display the numbers found
    //Assumption: numbers are separated by tabs and newlines
    //Recommended: random_numbers.txt
    fileio::process_file<int, float, double, long long>();

    //Call readFileToString, check current directory
    //std::cout << read_file_to_string("io demo.txt");

    //Call readFileToString, specify the directory. Note the use of forward slashes, even on Windows
    //std::cout << read_file_to_string("C:/Users/jacob/Documents/CodingPractice/C++/STL_FileIO", "io demo.txt");
}