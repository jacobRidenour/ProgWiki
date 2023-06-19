#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/chrono.hpp>

using string = std::string;

/* Function Declarations */
void show_cwd();

int main() {
    show_cwd();
    return 0;
}

void show_cwd() {
    boost::filesystem::path cwd;
    boost::chrono::system_clock::time_point start, end;

    start = boost::chrono::system_clock::now();
    cwd = boost::filesystem::current_path();
    end = boost::chrono::system_clock::now();

    std::string currentDirStr = cwd.string();
    boost::chrono::duration<double> duration = end - start;
    std::cout << "Current Directory: " << currentDirStr << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}