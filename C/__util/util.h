#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

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

#endif /* UTIL_H */