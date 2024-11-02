#ifndef CONSOLEIO_H
#define CONSOLEIO_H

/******************************************************************************
* ConsoleIO.h
*
* Basic console IO, technically file IO...
*
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

int getIntInput(const char* prompt);
float getFloatInput(const char* prompt);
void getStringInput(char* buffer, size_t size, const char* prompt);
char getCharInput(const char* prompt);
Date getDateInput(const char* prompt);

#endif /* CONSOLEIO_H */