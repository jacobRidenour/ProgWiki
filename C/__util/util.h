#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

/*******************************************************************************\
* util                                                                         *
* Common/generic functions I've written that are applicable in multiple places.*
*                                                                              *
*______________________________________________________________________________*/

/******************************************************************************
* trimNewline
*
* parameters: 
*  - str : char* ; a string ending in newline
*   
* returns: none
* 
* description: replaces the newline character(s) in str with the
* null-terminating character \0
* 
******************************************************************************/
void trimNewline(char* str)
{
    size_t len = strlen(str);

    #ifdef WIN32
    // newline is 2 chars: \r\n
    // Find your predefined macros (MSVC):
    // $ cl /EP /Zc:preprocessor /PD /nologo /TP empty.c
    // (no equivalent to /dev/null on Windows :( )
    if (len > 1 && str[len - 1] == '\n' && str[len - 2] == '\r')
        str[len - 2] = '\0';
    else if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
    #elif defined (linux)
    // newline is just \n
    // Find your predefined macros (gcc):
    // $ gcc -dM -E - < /dev/null
    if (len > 0 && str[len - 1] == '\n') 
        str[len - 1] = '\0';
    #endif 
}

/******************************************************************************
* dateIsValid
*
* parameters: 
*  - year : int ; an int holding a year
*  - month : int ; an int holding the month
*  - day : int ; an int holding the day
*   
* returns: bool
* 
* description: determines if the provided year, month, and day correspond to 
* a valid ISO date
* 
******************************************************************************/
bool dateIsValid(int year, int month, int day)
{
    bool isValid = true;

    // ISO date limitation
    if (year < 0 || year > 9999) return false;

    if (month < 1 || month > 12) return false;

    if (day < 1 || day > 31) return false;

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30) return false;
    }

    if (month == 2)
    {
        // leap year: divisible by 4 but not 100, unless also divisible by 400
        // e.g. 2000 was a leap year, but 1900 wasn't
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

        if (isLeapYear)
        {
            if (day > 29) return false;
        }
        else
        {
            if (day > 28) return false;
        }
    }

    return isValid;
}

/******************************************************************************
* charlenUtf8
*
* parameters: 
*  - c : unsigned char
*   
* returns: size_t
* 
* description: determines if the byte c is the start of a UTF-8 character, 
* which may be 1-4 bytes
* 
******************************************************************************/
size_t charlenUtf8(unsigned char c)
{
    if ((c & 0x80) == 0x00) return 1; // 1-byte (ASCII)
    else if ((c & 0xE0) == 0xC0) return 2;
    else if ((c & 0xF0) == 0xE0) return 3;
    else if ((c & 0xF8) == 0xF0) return 4;
    return 1;
}

/******************************************************************************
* printBinary
*
* parameters: 
*  - n : BINARY_WIDTH_TYPE
*   
* returns: none
* 
* description: prints the binary representation of n, based on the width of
* BINARY_WIDTH_TYPE, e.g. unsigned char, short, int, long long
* 
******************************************************************************/
#define BINARY_WIDTH_TYPE unsigned char
void printBinary(BINARY_WIDTH_TYPE n) 
{
    unsigned int bitWidth = sizeof(BINARY_WIDTH_TYPE) * CHAR_BIT;

    for (int i = bitWidth - 1; i >= 0; --i) 
    {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i != 0) 
        {
            printf(" ");
        }
    }
}

#endif /* UTIL_H */