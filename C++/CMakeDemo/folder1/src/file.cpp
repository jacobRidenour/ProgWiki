#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <iostream>

namespace demo {

// Function using boost::chrono to measure the duration of an operation
void measure_duration() {
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();

    // Simulate some work by sleeping
    boost::this_thread::sleep_for(boost::chrono::seconds(1));

    boost::chrono::steady_clock::time_point end = boost::chrono::steady_clock::now();
    boost::chrono::milliseconds ms = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start);
    std::cout << "Duration: " << ms.count() << "ms" << std::endl;
}

} // namespace demo
