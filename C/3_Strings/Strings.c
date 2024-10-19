#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int char_compare(const void* a, const void* b) {
    return ( *(char *)a - *(char *)b );
}

int main() {
    // String concatenation
    char dest[50] = "hello, "; // oversized so we can concatenate to it
    char src[] = "World";
    
    strcat(dest, src); // "hello, " -> "hello, World"
    printf("Concatenated string: %s\n", dest);

    // String to uppercase
    for(int i = 0; dest[i] != '\0'; ++i)
        dest[i] = toupper(dest[i]);
    printf("Uppercase string: %s\n", dest);

    // String to lowercase
    for(int i = 0; dest[i] != '\0'; ++i)
        dest[i] = tolower(dest[i]);
    printf("Lowercase string: %s\n", dest);

    // Sorting strings alphabetically
    char str[strlen(dest)];
    strcpy(str, dest);
    // -- Bring your own comparison function to qsort
    qsort(str, strlen(str), sizeof(char), char_compare);
    printf("Sorted string: '%s'\n", str);

    // Splitting strings with some delimiter
    char mystr[] = "hello,can,you,help,me,find,the,library,please";
    #define MAX_TOKENS 10
    char* tokens[MAX_TOKENS]; // arbitrary size, bigger than we need

    int tokensIdx = 0;  // don't go out of bounds + track how many we found
    char* delim = ",";
    char* token = strtok(mystr, delim); // "hello"
    
    while(token != NULL && tokensIdx < MAX_TOKENS) {
        tokens[tokensIdx] = malloc(strlen(token) + 1);
        if (tokens[tokensIdx] != NULL)
            strcpy(tokens[tokensIdx], token); // copy the token into tokens array
        tokensIdx++;
        token = strtok(NULL, delim);
    }

    printf("\nTokens found: %d\n", tokensIdx);
    for (int i = 0; i < tokensIdx; ++i) {
        printf("[%d]: %s\n", i+1, tokens[i]);
        free(tokens[i]);
    }
}