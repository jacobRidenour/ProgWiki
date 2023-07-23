/* Includes */
#include <iostream> //includes istream, ostream
#include <fstream>  //includes ifstream, otfstream (typedefs for basic_*<char>)
// fstream derives from iostream
#include <string>
#include <optional>

/* Using & Typedefs */
using string = std::string;

/* C++ & FileIO *//*
*
* Files viewed as sequence of bytes ending with EOF marker or at specific byte number (OS-dependent)
* 
* iostream - cout, cin, cerr, clog
* fstream - ifstream, ofstream
* 
*/

//std::ios_base::openmode - WARNING: these are implementation defined
// app - seek to end of stream before each write
// ate - seek to end of stream immediately after open (data can still be written anywhere)
// binary - open in binary mode
// in - open for reading
// out - open for writing (discard file's contents)
// trunc - discard stream contents when opening
// noreplace - open in exclusive mode (C++23)

// Sequential files

// fstream can be used for input or output
std::fstream openFile(const string& filename, std::ios_base::openmode mode) {
    std::fstream file(filename, mode);

    // Check if file opened successfully (overloaded ! operator)
    if (!file) {
        std::cerr << "Could not open " << filename << ": " << std::strerror(errno)  << "\n";
        throw std::runtime_error("Could not open" + filename);
    }

    std::clog << "File " << filename << " opened in " << mode << " mode.\n";
    return file;
}
// you can use ofstream.open("filename", mode) if ofstream initialized without parameters.
// if mode is not passed in, default is ios::out

// Pattern: get variables from user: int, string, double
void writeToFile(std::fstream& file) {
    int id{};
    string name{};
    double cost{};

    int count = 1;
    std::cout << "Enter the id, name, and cost (delimiter: whitespace). Enter EOF to end input.\n" << count << ": ";
    while (std::cin >> id >> name >> cost) {
        file << id << " " << name << " " << cost << "\n";
        count++;
        std::cout << count << ": ";
    }
}

// Pattern: add the string to the file
void writeToFile(std::ofstream& file, string addendum) {
    file << addendum;
}

// File-position pointer - offset (int), number of bytes from beginning
// istream.get() - byte where next input will occur
// ostream.put() - byte where next output will occur
// current locations - tellg() tellp()
// set locations - seekg(#) seekp(#)
    // optional second param - relative seek position ios::beg (default), ios::cur, ios::end
    // e.g. seekg(4, ios::end) - 4 bytes relative to the end of the stream
// .read() .write() based on location of put/get file-position pointer

// Random Access Files
// - File needs some specified structure to it, e.g. each line is 100 characters, something.

std::fstream createRandomAccessFile(const string& filename) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Could not create or open " + filename + ".");
    }

    std::clog << "Random access file " << filename << " created and opened for read/write.\n";
    return file;
}

// assumption: offset is from beginning of file
void writeDataToRandomAccessFile(std::fstream& file, int position, const string& data) {
    file.seekp(position, std::ios::beg);
    file.write(data.c_str(), data.size());
}