/*
Built-in techniques?
Common techniques
*/

#include <stdio.h>
#include <stdarg.h>

// Custom logging function using vsnprintf and va_list
void custom_log(const char *format, ...) {
    char buffer[256];  // Buffer to store the formatted string

    va_list args;
    va_start(args, format);  // Initialize the va_list with the last fixed argument

    // Use vsnprintf to format the variadic arguments into the buffer
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);  // Clean up the va_list

    // Output the log message (in this case, print to stdout)
    printf("LOG: %s\n", buffer);
}

int main() {
    custom_log("This is a number: %d", 42);
    custom_log("Hello, %s!", "World");
    custom_log("Temperature is %.2f degrees.", 23.456);

    return 0;
}
