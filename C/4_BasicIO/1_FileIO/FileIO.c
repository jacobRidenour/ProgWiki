#include <stdio.h>
#include <stdbool.h>

// Console IO
#include "ConsoleIO.h"
// File IO
#include "FormattedText.h"
#include "UnformattedText.h"
// Binary file IO
#include "BinaryIO.h"

//void consoleIO();
void binaryIO(bool formatted);

int main()
{
    // File IO
    //readFormattedText();
    //readUnformattedText();
    // Binary IO
    readFormattedBinary();
    readUnformattedBinary();
}
