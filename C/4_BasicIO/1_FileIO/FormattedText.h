#ifndef FORMATTEDTEXT_H
#define FORMATTEDTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/******************************************************************************
* FormattedText.h
*
* For reading and parsing the contents of _common/formatted.txt, as an example
* of parsing formatted data from a text file 
*
******************************************************************************/

#define MAX_LINE_LENGTH 256
#define MAX_ENTRIES 10

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

int readFormattedText() {
    FILE* file = fopen("../../../_common/formatted.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    ServerInfo servers[MAX_ENTRIES];
    EventLog events[MAX_ENTRIES];
    ErrorDetail errors[MAX_ENTRIES];
    int serverIndex = 0, eventIndex = 0, errorIndex = 0;

    char line[MAX_LINE_LENGTH];

    // Process sections
    
    //line[strcspn(line, "\n")] = '\0';  // Removes the trailing newline character
    //printf("LINE %d: %s\n", lineNum, line);
    // if(lineNum >0) {
    //     printf("LINE %d: ", lineNum);
    //     for (int i = 0; line[i] != '\0'; i++) {
    //         printf("%02X ", (unsigned char)line[i]);
    //     }
    //     printf("\n");
    // }
    //lineNum++;

    int lineNum = 1;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        lineNum++;
        //printf("LINE %d: %s\n", lineNum, line);
        if (strstr(line, "--- Server Information")) {
            if (serverIndex >= MAX_ENTRIES) {
                fprintf(stderr, "Unable to read more Server Information. Skipping.\n");
                continue;
            }
            else {
                if (fgets(line, MAX_LINE_LENGTH, file)) {
                    parseServerInfo(file, servers, &serverIndex, line);
                }
            }
        }
        else if (strstr(line, "--- Event Logs")) {
            if (eventIndex >= MAX_ENTRIES) {
                fprintf(stderr, "Unable to read more Event Logs. Skipping.\n");
                continue;
            }
            else {
                if (fgets(line, MAX_LINE_LENGTH, file)) {
                    parseEventLogs(file, events, &eventIndex, line);
                }
            }
        }
        else if (strstr(line, "--- Error Details")) {
            if (serverIndex >= MAX_ENTRIES) {
                fprintf(stderr, "Unable to read more Error Details. Skipping.\n");
                continue;
            }
            else {
                if (fgets(line, MAX_LINE_LENGTH, file)) {
                    parseErrorDetails(file, errors, &errorIndex, line);
                }
            }
        }
    }

    printf("\n--- Summary of Results ---");
    printf("\nEntries for Server Information: %d", serverIndex);
    printf("\nEntries for Event Logs: %d", eventIndex);
    printf("\nEntries for Error Details: %d\n", errorIndex);

    fclose(file);
    return 0;
}

void parseServerInfo(FILE* file, ServerInfo* servers, int* serverIndex, char* firstLine) {
    char line[MAX_LINE_LENGTH];
    strncpy(line, firstLine, MAX_LINE_LENGTH);
    bool isFirstLine = true;

    while (true) {
        trimNewline(line);        

        // New section, don't parse this line
        if (!isFirstLine && (strncmp(line, "---", 3) == 0)) return; 

        if (strstr(line, "[ServerID]")) {
            char* idStr = strstr(line, "]") + 1;
            servers[*serverIndex].serverId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "Location:")) {
            char* locStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].location, locStr, sizeof(servers[*serverIndex].location) - 1);
        }
        else if (strstr(line, "IP:")) {
            char* ipStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].ip, ipStr, sizeof(servers[*serverIndex].ip) - 1);
        }
        else if (strstr(line, "OS:")) {
            char* osStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].os, osStr, sizeof(servers[*serverIndex].os) - 1);
        }
        else if (strstr(line, "Status:")) {
            char* statusStr = strstr(line, ":") + 2;
            strncpy(servers[*serverIndex].status, statusStr, sizeof(servers[*serverIndex].status) - 1);
            (*serverIndex)++;
        }

        // if EOF || end of section
        if (!fgets(line, MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) {
            return;
        }
        isFirstLine = false;
    }
}

void parseEventLogs(FILE* file, EventLog* events, int* eventIndex, char* firstLine) {
    char line[MAX_LINE_LENGTH];
    strncpy(line, firstLine, MAX_LINE_LENGTH);
    bool isFirstLine = true;

    // New section, don't parse this line
    if (!isFirstLine && (strncmp(line, "---", 3) == 0)) return; 

    while (true) {
        trimNewline(line);

        if (strstr(line, "[EventID]")) {
            char* idStr = strstr(line, "EVT") + 3;  // Move to the ID number after "EVT"
            events[*eventIndex].eventId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "ServerID:")) {
            char* serverIdStr = strstr(line, ":") + 2;
            events[*eventIndex].serverId = (int)strtol(serverIdStr, NULL, 10);
        }
        else if (strstr(line, "Timestamp:")) {
            char* timestampStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].timestamp, timestampStr, sizeof(events[*eventIndex].timestamp) - 1);
        }
        else if (strstr(line, "Type:")) {
            char* typeStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].type, typeStr, sizeof(events[*eventIndex].type) - 1);
        }
        else if (strstr(line, "Message:")) {
            char* messageStr = strstr(line, ":") + 2;
            strncpy(events[*eventIndex].message, messageStr, sizeof(events[*eventIndex].message) - 1);
            (*eventIndex)++;
        }

        // if EOF || end of section
        if (!fgets(line, MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) {
            return;
        }
        isFirstLine = false;
    }
}

void parseErrorDetails(FILE* file, ErrorDetail* errors, int* errorIndex, char* firstLine) {
    char line[MAX_LINE_LENGTH];
    strncpy(line, firstLine, MAX_LINE_LENGTH);
    bool isFirstLine = true;

    // Keep this logic in case we expand formatted.txt later
    if (!isFirstLine && (strncmp(line, "---", 3) == 0)) return; 

    while (true) {
        trimNewline(line); 

        if (strstr(line, "[ErrorID]")) {
            char* idStr = strstr(line, "ERR") + 3;
            errors[*errorIndex].errorId = (int)strtol(idStr, NULL, 10);
        }
        else if (strstr(line, "ServerID:")) {
            char* serverIdStr = strstr(line, ":") + 2;
            errors[*errorIndex].serverId = (int)strtol(serverIdStr, NULL, 10);
        }
        else if (strstr(line, "Timestamp:")) {
            char* timestampStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].timestamp, timestampStr, sizeof(errors[*errorIndex].timestamp) - 1);
        }
        else if (strstr(line, "Severity:")) {
            char* severityStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].severity, severityStr, sizeof(errors[*errorIndex].severity) - 1);
        }
        else if (strstr(line, "ErrorCode:")) {
            char* errorCodeStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].errorCode, errorCodeStr, sizeof(errors[*errorIndex].errorCode) - 1);
        }
        else if (strstr(line, "Description:")) {
            char* descriptionStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].description, descriptionStr, sizeof(errors[*errorIndex].description) - 1);
        }
        else if (strstr(line, "Suggested Action:")) {
            char* actionStr = strstr(line, ":") + 2;
            strncpy(errors[*errorIndex].suggestedAction, actionStr, sizeof(errors[*errorIndex].suggestedAction) - 1);
            (*errorIndex)++;
        }

        // if EOF || end of section
        if (!fgets(line, MAX_LINE_LENGTH, file) || strncmp(line, "---", 3) == 0) {
            return;
        }
        isFirstLine = false;
    }
}

void trimNewline(char* str) {
    size_t len = strlen(str);

    #ifdef WIN32
    // newline is 2 chars: \r\n
    // Find your predefined macros (MSVC):
    // $ 
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


#endif /* FORMATTEDTEXT_H */