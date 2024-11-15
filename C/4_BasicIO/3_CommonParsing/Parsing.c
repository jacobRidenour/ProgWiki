/*
CSV parsing / navigation
XML parsing / navigation
JSON parsing / navigation
*/

#include <stdio.h>

#include "CsvParser.h"
#include "XmlParser.h"
#include "JsonParser.h"

void csvPrintRow(size_t rowIndex, const char** columns, size_t columnCount, void* userData)
{
    printf("Row %zu: ", rowIndex);
    for (size_t i = 0; i < columnCount; ++i)
    {
        printf("%s  %s", columns[i], (i < columnCount - 1) ? ", " : "\n");
    }
}

int main()
{
    CsvParserConfig cfg = 
    {
        .delimiter = ',',
        .quoteChar = '"',
        .quotedFieldsAllowed = true,
        .shouldTrimWhitespace = true,
        .rowHandler = csvPrintRow,
        .userData = NULL
    };

    parseCsvFile("../../../__common/data.csv", &cfg);
    
}