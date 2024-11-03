/*
IO: console     
IO: text files  
IO: binary files 
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// For parsing text
#include "ConsoleIO.h"
#include "FormattedText.h"
#include "UnformattedText.h"

int consoleIO();
int fileIO(bool formatted);

int main()
{
    consoleIO();
    fileIO(true);
    fileIO(false);
}

int fileIO(bool formatted)
{
    if(formatted) return readFormattedText();
    else return readUnformattedText();
    return 0;
}