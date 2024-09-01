#ifndef TESTS_SUMMARY_H
#define TESTS_SUMMARY_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#else
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"
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

    printf("\n********************************************************\n");
    printf("BEGIN tests for %s\n\n", testName);
}

void TestsSummaryPrintFooter(const char* testName) {

    int total = results.successes + results.failures;
    double passRate = ((double)results.successes / total) * 100;

    printf("\n%s Tests: ", testName);

#ifdef _WIN32
    COLOR_GREEN;
#else
    printf(COLOR_GREEN);
#endif
    printf("%d Passed", results.successes);

#ifdef _WIN32
    COLOR_RESET;
#else
    printf(COLOR_RESET);
#endif
    printf(", ");

#ifdef _WIN32
    COLOR_RED;
#else
    printf(COLOR_RED);
#endif
    printf("%d Failed", results.failures);

#ifdef _WIN32
    COLOR_RESET;
#else
    printf(COLOR_RESET);
#endif
    printf(" (");

#ifdef _WIN32
    if (results.failures == 0) COLOR_GREEN;
    else COLOR_RED;
#else
    if (results.failures == 0) printf(COLOR_GREEN);
    else printf(COLOR_RED);
#endif
    printf("%.2f%%", passRate);

#ifdef _WIN32
    COLOR_RESET;
#else
    printf(COLOR_RESET);
#endif
    printf(")\n");

    printf("\nEND tests for %s\n", testName);
    printf("********************************************************\n\n");

    results.successes = 0;
    results.failures = 0;
}

void TestsSummaryPrintResults(const char* testName, int successes, int failures) {
    results.successes += successes;
    results.failures += failures;
    
    int total = successes + failures;
    double passRate = ((double)successes / total) * 100;

    printf("%s Test Summary: (", testName);

#ifdef _WIN32
    if (failures == 0) COLOR_GREEN;
    else COLOR_RED;
    printf("%.2f%%", passRate);
    COLOR_RESET;
#else
    if (failures == 0) printf(COLOR_GREEN);
    else printf(COLOR_RED);
    printf("%.2f%%", passRate);
    printf(COLOR_RESET);
#endif
    printf(")\n");

#ifdef _WIN32
    COLOR_GREEN;
#else
    printf(COLOR_GREEN);
#endif
    printf("%d passed\n", successes);

#ifdef _WIN32
    COLOR_RED;
#else
    printf(COLOR_RED);
#endif
    printf("%d failed\n", failures);

#ifdef _WIN32
    COLOR_RESET;
#else
    printf(COLOR_RESET);
#endif
}

#endif /* TESTS_SUMMARY_H */