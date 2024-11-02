#ifndef FORMATTEDTEXT_H
#define FORMATTEDTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util.h"

/******************************************************************************
* FormattedText.h
*
* For reading and parsing the contents of _common/formatted.txt, as an example
* of parsing formatted data from a text file 
*
******************************************************************************/

#define FORMATTED_H_MAX_LINE_LENGTH 256
#define FORMATTED_H_MAX_ENTRIES 7

typedef struct {
    int serverId;
    char location[20];
    char ip[16];
    char os[30];
    char status[15];
} ServerInfo;

typedef struct {
    int eventId;
    int serverId;
    char timestamp[20];
    char type[10];
    char message[100];
} EventLog;

typedef struct {
    int errorId;
    int serverId;
    char timestamp[20];
    char severity[10];
    char errorCode[20];
    char description[100];
    char suggestedAction[100];
} ErrorDetail;

void parseServerInfo(FILE* file, ServerInfo* servers, int* serverIndex, char* firstLine);
void parseEventLogs(FILE* file, EventLog* events, int* eventIndex, char* firstLine);
void parseErrorDetails(FILE* file, ErrorDetail* errors, int* errorIndex, char* firstLine);
void trimNewline(char* line); // helper function

int readFormattedText()
{
    FILE* file = fopen("../../../_common/formatted.txt", "r");
    if (!file)
    {
        perror("Error opening file\n");
        return 1;
    }

    ServerInfo servers[FORMATTED_H_MAX_ENTRIES];
    EventLog events[FORMATTED_H_MAX_ENTRIES];
    ErrorDetail errors[FORMATTED_H_MAX_ENTRIES];
    int serverIndex = 0, eventIndex = 0, errorIndex = 0;
    char line[FORMATTED_H_MAX_LINE_LENGTH];
    
    // Process each section
    while (fgets(line, FORMATTED_H_MAX_LINE_LENGTH, file))
    {
        if (strstr(line, "--- Server Information"))
        {
            parseServerInfo(file, servers, &serverIndex, line);
            parseEventLogs(file, events, &eventIndex, line);
            parseErrorDetails(file, errors, &errorIndex, line);
        }
    }

    printf("\nFormatted Text processing summary");
    printf("\n=================================");
    printf("\nEntries for Server Information: %d", serverIndex);
    printf("\nEntries for Event Logs: %d", eventIndex);
    printf("\nEntries for Error Details: %d\n", errorIndex);

    fclose(file);
    return 0;
}

void parseServerInfo(FILE* file, ServerInfo* servers, int* serverIndex, char* firstLine)
{
    char line[FORMATTED_H_MAX_LINE_LENGTH];
    char prevLine[FORMATTED_H_MAX_LINE_LENGTH];
    strncpy(line, firstLine, FORMATTED_H_MAX_LINE_LENGTH);
    bool isFirstLine = true;

    while (true)
    {
        trimNewline(line);        

        // New section, make sure prevLine has its contents
        if (!isFirstLine && (strncmp(line, "---", 3) == 0))
        {
            strncpy(prevLine, line, FORMATTED_H_MAX_LINE_LENGTH);
            strncpy(line, prevLine, FORMATTED_H_MAX_LINE_LENGTH);
            return;
        }
        if (strstr(line, "[ServerID]"))
        {
            char* idStr = strstr(line, "]") + 1;
            servers[*serverIndex].serverId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "Location:"))
        {
            char* locStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].location, locStr, sizeof(servers[*serverIndex].location) - 1);
        }
        else if (strstr(line, "IP:"))
        {
            char* ipStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].ip, ipStr, sizeof(servers[*serverIndex].ip) - 1);
        }
        else if (strstr(line, "OS:"))
        {
            char* osStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].os, osStr, sizeof(servers[*serverIndex].os) - 1);
        }
        else if (strstr(line, "Status:"))
        {
            char* statusStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].status, statusStr, sizeof(servers[*serverIndex].status) - 1);
            (*serverIndex)++;
            if (*serverIndex >= FORMATTED_H_MAX_ENTRIES)
            {
                fprintf(stderr, "ERROR: Unable to parse more Server Information. Exiting.\n");
                exit(1);
            }
        }

        // if EOF || end of section
        if (!fgets(line, FORMATTED_H_MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) return;
        isFirstLine = false;
    }
}

void parseEventLogs(FILE* file, EventLog* events, int* eventIndex, char* firstLine)
{
    char line[FORMATTED_H_MAX_LINE_LENGTH];
    char prevLine[FORMATTED_H_MAX_LINE_LENGTH];
    strncpy(line, firstLine, FORMATTED_H_MAX_LINE_LENGTH);
    bool isFirstLine = true;

    if (!isFirstLine && (strncmp(line, "---", 3) == 0)) {
        strncpy(prevLine, line, FORMATTED_H_MAX_LINE_LENGTH);
        strncpy(line, prevLine, FORMATTED_H_MAX_LINE_LENGTH);
        return;
    }

    while (true)
    {
        trimNewline(line);

        if (strstr(line, "[EventID]"))
        {
            char* idStr = strstr(line, "EVT") + 3;
            events[*eventIndex].eventId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "ServerID:"))
        {
            char* serverIdStr = strstr(line, ":") + 2;
            events[*eventIndex].serverId = (int)strtol(serverIdStr, NULL, 10);
        }
        else if (strstr(line, "Timestamp:"))
        {
            char* timestampStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].timestamp, timestampStr, sizeof(events[*eventIndex].timestamp) - 1);
        }
        else if (strstr(line, "Type:"))
        {
            char* typeStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].type, typeStr, sizeof(events[*eventIndex].type) - 1);
        }
        else if (strstr(line, "Message:"))
        {
            char* messageStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].message, messageStr, sizeof(events[*eventIndex].message) - 1);
            (*eventIndex)++;
            if (*eventIndex >= FORMATTED_H_MAX_ENTRIES)
            {
                fprintf(stderr, "ERROR: Unable to parse more Event Logs. Exiting.\n");
                exit(1);
            }
        }

        // if EOF || end of section
        if (!fgets(line, FORMATTED_H_MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) return;
        isFirstLine = false;
    }
}

void parseErrorDetails(FILE* file, ErrorDetail* errors, int* errorIndex, char* firstLine)
{
    char line[FORMATTED_H_MAX_LINE_LENGTH];
    strncpy(line, firstLine, FORMATTED_H_MAX_LINE_LENGTH);
    bool isFirstLine = true;

    // Keep this logic in case we expand formatted.txt later
    if (!isFirstLine && (strncmp(line, "---", 3) == 0)) return; 

    while (true) {
        trimNewline(line); 

        if (strstr(line, "[ErrorID]"))
        {
            char* idStr = strstr(line, "ERR") + 3;
            errors[*errorIndex].errorId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "ServerID:"))
        {
            char* serverIdStr = strstr(line, ":") + 2;
            errors[*errorIndex].serverId = (int)strtol(serverIdStr, NULL, 10);
        }
        else if (strstr(line, "Timestamp:"))
        {
            char* timestampStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].timestamp, timestampStr, sizeof(errors[*errorIndex].timestamp) - 1);
        }
        else if (strstr(line, "Severity:"))
        {
            char* severityStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].severity, severityStr, sizeof(errors[*errorIndex].severity) - 1);
        }
        else if (strstr(line, "ErrorCode:"))
        {
            char* errorCodeStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].errorCode, errorCodeStr, sizeof(errors[*errorIndex].errorCode) - 1);
        }
        else if (strstr(line, "Description:"))
        {
            char* descriptionStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].description, descriptionStr, sizeof(errors[*errorIndex].description) - 1);
        }
        else if (strstr(line, "Suggested Action:"))
        {
            char* actionStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].suggestedAction, actionStr, sizeof(errors[*errorIndex].suggestedAction) - 1);
            (*errorIndex)++;
            if (*errorIndex >= FORMATTED_H_MAX_ENTRIES)
            {
                fprintf(stderr, "ERROR: Unable to parse more Error Details. Exiting.\n");
                exit(1);
            }
        }

        // if EOF || end of section
        if (!fgets(line, FORMATTED_H_MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) return;

        isFirstLine = false;
    }
}

#endif /* FORMATTEDTEXT_H */