#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    CSV_SUCCESS = 1,
    CSV_ERR_NULL_INPUT,
    CSV_ERR_MEMORY_ALLOCATION,
    CSV_ERR_UNBALANCED_QUOTES,
    CSV_ERR_COLUMN_INDEX_OUT_OF_RANGE
} CsvErrorCode;

// Map error codes to messages
const char* csvErrorMessage(CsvErrorCode code);

// Callback for handling parsed rows
typedef void (*CsvRowHandler)(size_t rowIndex, const char** columns, size_t columnCount, void* userData);

// Configuration structure for the CSV parser
typedef struct {
    char delimiter;            // Delimiter character (e.g., ',')
    char quoteChar;            // Quote character (e.g., '"')
    bool quotedFieldsAllowed;  // Whether quoted fields are allowed
    bool shouldTrimWhitespace; // Whether to trim leading/trailing whitespace
    CsvRowHandler rowHandler;  // Callback for processing rows
    void* userData;            // User-defined data for callback
} CsvParserConfig;

// Main parsing function
bool parseCsvFile(const char* filePath, const CsvParserConfig* config);

// Utility function to split a single CSV line into columns
bool parseCsvLine(const char* line, const CsvParserConfig* config, char*** columns, size_t* columnCount);

// Utility function to free allocated columns
void freeCsvColumns(char** columns, size_t columnCount);

// Add/drop a column by index
CsvErrorCode addCsvColumn(char*** rows, size_t rowCount, const char* defaultValue);
CsvErrorCode dropCsvColumn(char*** rows, size_t rowCount, size_t columnIndex);

#endif /* CSVPARSER_H */