#ifndef PRINT_TEST_RESULTS_H
#define PRINT_TEST_RESULTS_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Simple way to print unit test results to the console.
// Formatting is like so:
/*

****************************************
TestName Results ({passRate}%)
{successes} passed
{failures} failed 
****************************************

*/

void print_test_results(const char* testName, int successes, int failures) {
    int total = successes + failures;
    double passRate = ((double)successes / total) * 100;

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    printf("****************************************\n");
    printf("%s Results (", testName);

#ifdef _WIN32
    if (failures == 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }
    else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    }
    printf("%.2f%%", passRate);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    if (failures == 0) {
        printf("\033[0;32m%.2f%%\033[0m", passRate);  // Green
    } else {
        printf("\033[0;31m%.2f%%\033[0m", passRate);  // Red
    }
#endif

    printf(")\n");

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
#else
    printf("\033[0;32m");  // Green
#endif
    printf("%d passed\n", successes);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
#else
    printf("\033[0;31m");  // Red
#endif
    printf("%d failed\n", failures);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    printf("\033[0m");  // Reset color to default
#endif

    printf("****************************************\n");
}

#endif