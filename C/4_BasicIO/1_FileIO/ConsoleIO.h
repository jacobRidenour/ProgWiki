#ifndef CONSOLEIO_H
#define CONSOLEIO_H

/******************************************************************************
* ConsoleIO.h
*
* Basic console IO, technically file IO...
*
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "util.h"

typedef struct {
    int day;
    int month;
    int year;
} Date;


void getStringInput(char* buffer, size_t size, const char* prompt);
long long getIntInput(const char* prompt); // wider than they need to be just 'cuz
long double getFloatInput(const char* prompt);
char getCharInput(const char* prompt);
Date getDateInput(const char* prompt);

int consoleIO()
{
    char name[100];
    getStringInput(name, sizeof name, "Enter your full name (max 100 chars): ");
    long long age = getIntInput("Enter your age: ");
    long double height = getFloatInput("Enter your height in meters (e.g., 1.75): ");
    char letter = getCharInput("Enter your favorite letter: ");
    Date dob = getDateInput("Enter your date of birth (format YYYY-MM-DD): ");

    // Display collected data
    printf("\n\nConsoleI/O parsing summary");
    printf("\n==========================");
    printf("\nName: %s", name);
    printf("\nAge: %lld", age);
    printf("\nHeight: %.2Lf meters", height);
    printf("\nFavorite letter: %c", letter);
    printf("\nDate of Birth: %04d-%02d-%02d\n", dob.year, dob.month, dob.day);

    return 0;
}

void getStringInput(char* buffer, size_t size, const char* prompt)
{
    // Continue until correct input
    while(1)
    {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL)
        {
            // Flush the buffer if user input more than <size-1> chars
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            bool nameIsValid = true;
            int numAlphas = 0;
            size_t i = 0;
            for (; i < size && buffer[i] != '\n'; ++i)
            {
                // Input sanitization: allow only whitespace / alphabetical chars
                
                // Name can't contain only whitespace
                if(isalpha(buffer[i])) numAlphas++;
                if (numAlphas == 0)
                {
                    nameIsValid = false;
                    break;
                }

                if (!(isalpha(buffer[i]) || buffer[i] == ' '))
                {
                    nameIsValid = false;
                    break;
                }
            }
            // buffer ends in newline unless
            // we have read in <size-1> chars
            trimNewline(buffer);

            if (nameIsValid) break;
            else fprintf(stderr, "Invalid input. Please use alphabetic characters only.\n");

        }
        else
        {
            perror("Error: unable to read input from console\n");
            buffer[0] = '\0';
            exit(1);
        }
    }
}

long long getIntInput(const char* prompt)
{
    char buffer[22];
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            // Flush the buffer if user input more than 21 chars
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            trimNewline(buffer);

            char* endPtr;
            long long value = strtoll(buffer, &endPtr, 0);
            // base 0 = automatically interpret as octal, hex, or decimal

            // Check if the entire input was a valid integral type
            if (endPtr != buffer && *endPtr == '\0') return value;
            else fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
        }
        else
        {
            perror("Error: unable to read input from console\n");
            exit(1);
        }
    }
}

long double getFloatInput(const char* prompt)
{
    char buffer[22];
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            // Flush the buffer if user input more than 21 chars
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            trimNewline(buffer);

            char* endPtr;
            long double value = strtold(buffer, &endPtr);

            // Check if the entire input was a valid floating-point type
            if (endPtr != buffer && *endPtr == '\0') return value;
            else fprintf(stderr, "Invalid input. Please enter a valid floating-point number.\n");
        }
        else
        {
            perror("Error: unable to read input from console\n");
            exit(1);
        }
    }
}

char getCharInput(const char* prompt)
{
    char buffer[3];
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof buffer, stdin) != NULL)
        {
            // Flush the buffer if user input more than 2 chars
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            trimNewline(buffer);

            // Check that the input is a single alphabetical character
            if (strlen(buffer) == 1 && isalpha(buffer[0])) return buffer[0];
            else fprintf(stderr, "Invalid input. Please enter a single alphabetical character.\n");
        }
        else
        {
            perror("Error: unable to read input from console\n");
            exit(1);
        }
    }
}

Date getDateInput(const char* prompt)
{
    char buffer[15];
    Date date;
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Flush the buffer if user input more than 14 chars
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            trimNewline(buffer);

            // Validate and parse date in the format YYYY-MM-DD
            if (sscanf(buffer, "%4d-%2d-%2d", &date.year, &date.month, &date.day) == 3)
            {
                // Check if the parsed values form a valid date
                if (dateIsValid(date.year, date.month, date.day)) return date;
                else fprintf(stderr, "Invalid date. Day must be 1-31 and month 1-12.\n");
            }
            else fprintf(stderr, "Invalid input. Please enter date in ISO format YYYY-MM-DD.\n");
        }
        else
        {
            perror("Error: unable to read input from console\n");
            exit(1);
        }
    }
}

#endif /* CONSOLEIO_H */