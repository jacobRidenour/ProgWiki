#include <stdio.h>
#include <stdbool.h>

// Console IO
#include "ConsoleIO.h"
// File IO
#include "FormattedText.h"
#include "UnformattedText.h"
// Binary file IO
#include "BinaryIO.h"

int main()
{
    // Console IO (special case of file IO)
    consoleIO();
    // File IO
    readFormattedText();
    readUnformattedText();
    // Binary IO
    readFormattedBinary();
    readUnformattedBinary();
}
