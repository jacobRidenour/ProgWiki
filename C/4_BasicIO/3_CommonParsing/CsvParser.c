#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "CsvParser.h"

// Map error code to a message
const char* csvErrorMessage(CsvErrorCode code) 
{
    switch (code) {
        case CSV_SUCCESS: return "Success";
        case CSV_ERR_NULL_INPUT: return "Null input provided";
        case CSV_ERR_MEMORY_ALLOCATION: return "Memory allocation failed";
        case CSV_ERR_UNBALANCED_QUOTES: return "Unbalanced quotes in field";
        case CSV_ERR_COLUMN_INDEX_OUT_OF_RANGE: return "Column index out of range";
        default: return "Unknown error";
    }
}

// Internal helper to trim whitespace - move to utils?
static char* __trimWhitespace(char* str)
{
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}

// Replace double quotes ("") with a single quote (")
static void __normalizeEscapedQuotes(char *field, char quoteChar)
{
    if (!field) return;

    size_t readIndex = 0, writeIndex = 0;

    while (field[readIndex] != '\0')
    {
        if (field[readIndex] == quoteChar && field[readIndex + 1] == quoteChar)
        {
            // Encountered "" (escaped quote), replace with a single "
            field[writeIndex++] = quoteChar;
            readIndex += 2; // Skip the second quote
        }
        else
        {
            // Copy the character as is
            field[writeIndex++] = field[readIndex++];
        }
    }

    // Null-terminate the normalized string
    field[writeIndex] = '\0';
}


// Parse a CSV file line by line
bool parseCsvFile(const char* filePath, const CsvParserConfig* config)
{
    if (!filePath || !config || !config->rowHandler) return false;

    FILE* file = fopen(filePath, "r");
    if (!file) return false;

    char* line = NULL;
    size_t len = 0;
    size_t rowIndex = 0;

    while (getline(&line, &len, file) != -1)
    {
        char** columns = NULL;
        size_t columnCount = 0;

        if (parseCsvLine(line, config, &columns, &columnCount))
        {
            config->rowHandler(rowIndex++, (const char**)columns, columnCount, config->userData);
            freeCsvColumns(columns, columnCount);
        }
        else
        {
            fprintf(stderr, "Failed to parse line %zu in CSV file", columnCount);
            return false;
        }
    }

    free(line);
    fclose(file);
    return true;
}

// Internal helper to split a line into columns
bool parseCsvLine(const char* line, const CsvParserConfig* config, char*** columns, size_t* columnCount) {
    if (!line || !config || !columns || !columnCount)
    {
        if(!line) fprintf(stderr, "%s: line", csvErrorMessage(CSV_ERR_NULL_INPUT));
        if(!config) fprintf(stderr, "%s: config", csvErrorMessage(CSV_ERR_NULL_INPUT));
        if(!columns) fprintf(stderr, "%s: columns", csvErrorMessage(CSV_ERR_NULL_INPUT));
        if(!columnCount) fprintf(stderr, "%s: columnCount", csvErrorMessage(CSV_ERR_NULL_INPUT));
        return false;
    }

    size_t capacity = 10;
    *columns = malloc(capacity * sizeof(char*));
    if (!*columns) 
    {
        fprintf(stderr, "%s: allocating space for columns", csvErrorMessage(CSV_ERR_MEMORY_ALLOCATION));
        return false;
    }

    *columnCount = 0;
    const char *start = line;
    const char *end;
    bool inQuotes = false;

    while (*start) {
        if (*columnCount >= capacity)
        {
            capacity *= 2;
            char** temp = realloc(*columns, capacity * sizeof(char*));
            if (!temp)
            {
                freeCsvColumns(*columns, *columnCount);
                return false;
            }
            *columns = temp;
        }

        if (*start == config->quoteChar && config->quotedFieldsAllowed)
        {
            inQuotes = !inQuotes;
            start++;
        }

        end = start;
        while (*end && (inQuotes || *end != config->delimiter))
        {
            // Skip escaped quote e.g. ""
            if (inQuotes && *end == config->quoteChar && *(end+1) == config->quoteChar)
            {
                end++;
            }
            else if (*end == config->quoteChar && config->quotedFieldsAllowed)
            {
                inQuotes = !inQuotes;
            }
            end++;
        }

        if (inQuotes)
        {
            freeCsvColumns(*columns, *columnCount);
            return CSV_ERR_UNBALANCED_QUOTES;
        }

        size_t len = end - start;
        (*columns)[*columnCount] = strndup(start, len);

        // trim whitespace if set
        if (config->shouldTrimWhitespace) (*columns)[*columnCount] = __trimWhitespace((*columns)[*columnCount]);

        // normalize escaped quotes, if allowed
        if (config->quotedFieldsAllowed) __normalizeEscapedQuotes((*columns)[*columnCount], config->quoteChar);

        (*columnCount)++;
        start = (*end) ? end + 1 : end;
    }

    return CSV_SUCCESS;
}

// Free allocated columns
void freeCsvColumns(char** columns, size_t columnCount)
{
    for (size_t i = 0; i < columnCount; ++i)
    {
        free(columns[i]);
    }
    free(columns);
}

// Add a new column to all rows
CsvErrorCode addCsvColumn(char*** rows, size_t rowCount, const char* defaultValue)
{
    if (!rows) return CSV_ERR_NULL_INPUT;

    for (size_t i = 0; i < rowCount; i++)
    {
        char **row = rows[i];
        size_t colCount = 0;

        while (row[colCount] != NULL) colCount++;

        char **newRow = realloc(row, (colCount + 2) * sizeof(char *));
        if (!newRow) return CSV_ERR_MEMORY_ALLOCATION;

        newRow[colCount] = strdup(defaultValue ? defaultValue : "");
        newRow[colCount + 1] = NULL;
        rows[i] = newRow;
    }

    return CSV_SUCCESS;
}

// Drop a column by index
CsvErrorCode dropCsvColumn(char*** rows, size_t rowCount, size_t columnIndex)
{
    if (!rows) return CSV_ERR_NULL_INPUT;

    for (size_t i = 0; i < rowCount; ++i)
    {
        char** row = rows[i];
        size_t colCount = 0;

        // Find column count for each row
        while (row[colCount] != NULL) colCount++;
        if (columnIndex >= colCount) return CSV_ERR_COLUMN_INDEX_OUT_OF_RANGE;

        free(row[columnIndex]);
        for (size_t j = columnIndex; j < colCount - 1; j++)
        {
            row[j] = row[j + 1];
        }
        row[colCount - 1] = NULL;
    }

    return CSV_SUCCESS;
}
