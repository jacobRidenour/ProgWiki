#include <stdio.h> // #include -> Preprocessor: copy stdio.h into this file
                   // <file.h> - search system paths before project paths

// ******************************
// Function main
// @return: int
// @param argc - argument count
// @param argv - the arguments
// ******************************
int main(int argc, char* argv[]) {
    // Note, argc is always at least 1; the first argument is the program name
    printf("hello, world\n");
    // For main() only, if we don't explicitly return any value, a value of 0
    // is returned.
}