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
#define MAX_ENTRIES 2

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

void parseServerInfo(FILE* file, ServerInfo* servers, int* serverIndex);
void parseEventLogs(FILE* file, EventLog* events, int* eventIndex);
void parseErrorDetails(FILE* file, ErrorDetail* errors, int* errorIndex);

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
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Assumption: No subsections
        if (strstr(line, "--- Server Information")) parseServerInfo(file, servers, &serverIndex);
        else if (strstr(line, "--- Event Logs")) parseEventLogs(file, events, &eventIndex);
        else if (strstr(line, "--- Error Details")) parseErrorDetails(file, errors, &errorIndex);
    }

    printf("\n--- Summary of Results ---");
    printf("\nEntries for Server Information: %d", serverIndex);
    printf("\nEntries for Event Logs: %d", eventIndex);
    printf("\nEntries for Error Details: %d\n", errorIndex);

    fclose(file);
    return 0;
}

void parseServerInfo(FILE* file, ServerInfo* servers, int* serverIndex) {
    static bool haveCapacity = true; // handling if we've hit MAX_ENTRIES
    if (!haveCapacity) {
        printf("parseServerInfo skipped: no capacity left.\n");
        return;
    }

    if (!haveCapacity) return;
    else {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, file) && line[0] != '-') {
            if (strstr(line, "[ServerID]")) {
                sscanf(line, "[ServerID] %d", &servers[*serverIndex].serverId);
            }
            else if (strstr(line, "Location:")) {
                sscanf(line, " Location: %19[^\n]", servers[*serverIndex].location);
            }
            else if (strstr(line, "IP:")) {
                sscanf(line, " IP: %15[^\n]", servers[*serverIndex].ip);
            }
            else if (strstr(line, "OS:")) {
                sscanf(line, " OS: %29[^\n]", servers[*serverIndex].os);
            } 
            else if (strstr(line, "Status:")) {
                sscanf(line, " Status: %14[^\n]", servers[*serverIndex].status);
                (*serverIndex)++;
                if (*serverIndex >= MAX_ENTRIES) {
                    fprintf(stderr, "Unable to read more Server Information. Stopping.\n");
                    haveCapacity = false;
                    printf("Capacity reached, haveCapacity set to false.\n");
                }
            }
        } // end while
    }
}

void parseEventLogs(FILE* file, EventLog* events, int* eventIndex) {
    static bool haveCapacity = true;
    if (!haveCapacity) return;
    else {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, file) && line[0] != '-') {
            if (strstr(line, "[EventID]")) {
                sscanf(line, "[EventID] EVT%03d", &events[*eventIndex].eventId);
            }
            else if (strstr(line, "ServerID:")) {
                sscanf(line, " ServerID: %d", &events[*eventIndex].serverId);
            }
            else if (strstr(line, "Timestamp:")) {
                sscanf(line, " Timestamp: %19[^\n]", events[*eventIndex].timestamp);
            }
            else if (strstr(line, "Type:")) {
                sscanf(line, " Type: %9[^\n]", events[*eventIndex].type);
            }
            else if (strstr(line, "Message:")) {
                sscanf(line, " Message: %99[^\n]", events[*eventIndex].message);
                if (*eventIndex + 1 >= MAX_ENTRIES) {
                    fprintf(stderr, "Unable to read more Event Logs. Stopping.\n");
                    haveCapacity = false;
                }
                (*eventIndex)++;
            }
        } // end while
    }
}

void parseErrorDetails(FILE* file, ErrorDetail* errors, int* errorIndex) {
    static bool haveCapacity = true; // handling if we've hit MAX_ENTRIES
    if (!haveCapacity) return;
    else {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, file) && line[0] != '-') {
            if (strstr(line, "[ErrorID]")) {
                sscanf(line, "[ErrorID] ERR%03d", &errors[*errorIndex].errorId);
            }
            else if (strstr(line, "ServerID:")) {
                sscanf(line, " ServerID: %d", &errors[*errorIndex].serverId);
            }
            else if (strstr(line, "Timestamp:")) {
                sscanf(line, " Timestamp: %19[^\n]", errors[*errorIndex].timestamp);
            }
            else if (strstr(line, "Severity:")) {
                sscanf(line, " Severity: %9[^\n]", errors[*errorIndex].severity);
            }
            else if (strstr(line, "ErrorCode:")) {
                sscanf(line, " ErrorCode: %19[^\n]", errors[*errorIndex].errorCode);
            }
            else if (strstr(line, "Description:")) {
                sscanf(line, " Description: %99[^\n]", errors[*errorIndex].description);
            }
            else if (strstr(line, "Suggested Action:")) {
                sscanf(line, " Suggested Action: %99[^\n]", errors[*errorIndex].suggestedAction);
                if (*errorIndex + 1 >= MAX_ENTRIES) {
                    fprintf(stderr, "Unable to read more Server Information. Stopping.\n");
                    haveCapacity = false;
                }
                (*errorIndex)++;
            }
        } // end while
    }
}

#endif /* FORMATTEDTEXT_H */