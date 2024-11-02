#ifndef UNFORMATTEDTEXT_H
#define UNFORMATTEDTEXT_H

/******************************************************************************
* UnformattedText.h
*
* For reading and parsing the contents of _common/unformatted.txt, as an example
* of parsing loosely formatted data from a text file 
*
******************************************************************************/

#include <ctype.h>

#define UNFORMATTED_H_MAX_ENTRIES 100
#define UNFORMATTED_H_MAX_LINE_LENGTH 256

typedef struct {
    char customerName[50];
    char feedback[500];
    char date[15];
    int stars;
} Feedback;

int extractStars(char* line);
int extractDate(char* line, char* dateBuffer);
void parseFeedback(char* line, Feedback* feedback);

int readUnformattedText()
{
    FILE* file = fopen("../../../_common/unformatted.txt", "r");
    if (!file)
    {
        perror("Error opening file\n");
        return 1;
    }

    Feedback feedbacks[UNFORMATTED_H_MAX_ENTRIES];
    int feedbackIndex = 0;
    char line[UNFORMATTED_H_MAX_LINE_LENGTH];

    while (fgets(line, UNFORMATTED_H_MAX_LINE_LENGTH, file) && feedbackIndex < UNFORMATTED_H_MAX_ENTRIES) {
        parseFeedback(line, &feedbacks[feedbackIndex]);
        feedbackIndex++;
    }

    // Show parsed input
    printf("\nUnformatted Text processing summary");
    printf("\n===================================");

    printf("\n%-20s %-15s %-5s\n", "Customer Name", "Date", "Stars");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < feedbackIndex; ++i)
    {
        printf("%-20s %-15s %-5d\n", 
            feedbacks[i].customerName[0] ? feedbacks[i].customerName : "Unknown",
            feedbacks[i].date[0] ? feedbacks[i].date : "No Date",
            feedbacks[i].stars);
    }


    fclose(file);
    return 0;
}

void parseFeedback(char* line, Feedback* feedback)
{
    memset(feedback, 0, sizeof(Feedback));

    // Parse name; requirement/assumption, each review
    // starts with a name, which ends with a period
    char* period = strchr(line, '.');
    if (period)
    {
        int nameLength = period - line;
        if (nameLength < sizeof(feedback->customerName))
        {
            strncpy(feedback->customerName, line, nameLength);
            feedback->customerName[nameLength] = '\0';
        }
    }

    // Parse date; candidates: ISO format, full month + day, abbrev. month + day
    extractDate(line, feedback->date);

    // Parse rating
    feedback->stars = extractStars(line);

    // Read feedback text
    snprintf(feedback->feedback, sizeof(feedback->feedback), "%s", line);
}

#include <regex.h>

int extractDate(char *line, char *dateBuffer)
{
    const char* months[] = { "January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December",
                             "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    int monthCount = sizeof(months) / sizeof(months[0]);

    // Check for ISO format date (YYYY-MM-DD)
    for (int i = 0; line[i+9] != '\0'; ++i)
    {
        if (isdigit(line[i]) && isdigit(line[i+1]) && isdigit(line[i+2]) && isdigit(line[i+3])
            && line[i+4] == '-'
            && isdigit(line[i+5]) && isdigit(line[i+6])
            && line[i+7] == '-'
            && isdigit(line[i+8]) && isdigit(line[i+9]))
        {
            // Extract the date substring
            strncpy(dateBuffer, line + i, 10);
            dateBuffer[10] = '\0';
            return 1;
        }
    }

    // Check for "Month Day" or "Mon Day" format
    for (int i = 0; i < monthCount; ++i)
    {
        char* monthPtr = strstr(line, months[i]);
        if (monthPtr)
        {
            // whole worlds only; avoid e.g. "Mark" getting parsed as "Mar k"
            char before = (monthPtr > line) ? *(monthPtr - 1) : ' ';
            char after = *(monthPtr + strlen(months[i]));
            
            if (!isalpha(before) && !isalpha(after))
            {
                char dayPart[3];
                if (sscanf(monthPtr + strlen(months[i]), " %2s", dayPart) == 1)
                {
                    // Remove any non-digit characters from dayPart,
                    // e.g. trailing commas or other junk
                    char cleanedDayPart[3] = {0};
                    int j = 0;
                    for (int k = 0; k < 2 && dayPart[k] != '\0'; k++)
                    {
                        if (isdigit(dayPart[k]))
                        {
                            cleanedDayPart[j++] = dayPart[k];
                        }
                    }
                    
                    snprintf(dateBuffer, 15, "%s %s", months[i], cleanedDayPart);
                    return 1;
                }
            }
        }
    }

    // If no date is found
    strcpy(dateBuffer, "No Date");
    return 0;
}

int extractStars(char *line)
{
    int stars = 0;

    // Possible format: with ⭐ characters
    char *starPtr = line;
    while ((starPtr = strstr(starPtr, "⭐")) != NULL)
    {
        stars++;
        starPtr += strlen("⭐");
    }

    // Other formats: "m/n stars" or "n stars"
    if (stars == 0) {
        int rating = 0;
        char* ptr;

        // "n/5 stars"
        ptr = strstr(line, "/5 stars");
        if (ptr != NULL)
        {
            // find the start of the number before "/5 stars"
            int pos = ptr - line;
            while (pos > 0 && isdigit(line[pos - 1])) pos--;
            if (sscanf(line + pos, "%d", &rating) == 1)
            {
                stars = rating;
                return stars;
            }
        }

        // "n stars" (important to do this after n/5, otherwise
        // it will get tripped inappropriately)
        ptr = strstr(line, " stars");
        if (ptr != NULL) {
            // find the start of the number before " stars"
            int pos = ptr - line;
            while (pos > 0 && isdigit(line[pos - 1])) pos--;
            if (sscanf(line + pos, "%d", &rating) == 1)
            {
                stars = rating;
                return stars;
            }
        }
    }
    return stars;
}

#endif /* UNFORMATTEDTEXT_H */