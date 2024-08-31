#ifndef TESTS_SUMMARY_H
#define TESTS_SUMMARY_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*******************************************************************************
Simple way to print unit test results to the console.
Formatting is like so:

********************************************************
BEGIN tests for {testName}

TestName Test Summary ({passRate}%)
{successes} passed
{failures} failed 

{x}/{y} tests succeeded.

END tests for {testName}
********************************************************

*******************************************************************************/

typedef struct {
    int successes;
    int failures;
} TestsSummary;

TestsSummary results;


void TestsSummaryPrintHeader(const char* testName) {
    results.successes = 0;
    results.failures = 0;

    printf("********************************************************\n");
    printf("BEGIN tests for %s\n\n", testName);
}

void TestsSummaryPrintFooter(const char* testName) {

    int total = results.successes + results.failures;
    double passRate = ((double)results.successes / total) * 100;

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    printf("\n%s Tests: ", testName);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
#else
    printf("\033[0;32m");  // Green
#endif
    printf("%d Passed", results.successes);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
#else
    printf("\033[0;31m");  // Red
#endif
    printf(", %d Failed", results.failures);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    printf("\033[0m");  // Reset color to default
#endif
    printf(" (");

    // Apply color for passRate
#ifdef _WIN32
    if (results.failures == 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    }
    else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    }
#else
    if (results.failures == 0) {
        printf("\033[0;32m");  // Green
    }
    else {
        printf("\033[0;31m");  // Red
    }
#endif
    printf("%.2f%%", passRate);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    printf("\033[0m");
#endif

    printf(")\n");

    printf("\nEND tests for %s\n", testName);
    printf("********************************************************\n");

    results.successes = 0;
    results.failures = 0;
}


void TestsSummaryPrintResults(const char* testName, int successes, int failures) {
    results.successes += successes;
    results.failures += failures;
    
    int total = successes + failures;
    double passRate = ((double)successes / total) * 100;

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    printf("%s Test Summary: (", testName);

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
}

#endif /* TESTS_SUMMARY_H */