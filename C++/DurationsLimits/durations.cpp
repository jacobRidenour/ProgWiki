#include <iostream>
#include <chrono>
#include <limits>

void durationDemonstration();
void showLimits();

int main() {
    durationDemonstration();
    showLimits();
    
    return 0;
}

void durationDemonstration() {
    // Start the timer
    auto startTime = std::chrono::steady_clock::now();

    std::vector<float> vec(1000000, 0.45);
    

    // Perform some time-consuming operation
    for (int i = 0; i < 1000000; ++i) {
        if (i % 2 == 0) vec[i] += 0.3;
        else vec[i] += 0.41;
    }

    // End the timer
    auto endTime = std::chrono::steady_clock::now();

    // Calculate the duration
    auto duration = endTime - startTime;

    // Convert duration to different units
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);

    // Report the time spent
    std::cout << "Time spent: " << seconds.count() << " s /" << milliseconds.count() << " ms /" << microseconds.count() << " us" << std::endl;

    // Conversion of doubles to duration objects
    double timeInSeconds = 2.5;
    auto durationInSeconds = std::chrono::duration<double>(timeInSeconds);

    // Conversion of duration objects to doubles
    double durationInSecondsDouble = std::chrono::duration<double>(duration).count();
    std::cout << "Duration in seconds (double): " << durationInSecondsDouble << std::endl;
}

void showLimits() {
    auto printLimits = [](auto value) {
        std::cout << "Type: " << typeid(decltype(value)).name() << " (" << sizeof(decltype(value)) << " bytes)" << std::endl;
        std::cout << "Minimum: " << std::numeric_limits<decltype(value)>::min() << std::endl;
        std::cout << "Maximum: " << std::numeric_limits<decltype(value)>::max() << std::endl;
        std::cout << std::endl;
    };

    printLimits(static_cast<int>(0));
    printLimits(static_cast<long long>(0));
    printLimits(static_cast<float>(0));
    printLimits(static_cast<double>(0));
}