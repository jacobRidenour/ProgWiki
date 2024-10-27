/*
IO: console     
IO: text files  
IO: binary files 
*/

#include <stdio.h>

void consoleIO();

int main() {
    consoleIO();
}

// (Formatted) console IO
// todo unformatted? nah
void consoleIO() {
    char nameBuff[50];
    
    // Read a string from the console into a variable
    printf("Enter your name: ");
    if (fgets(nameBuff, sizeof(nameBuff), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }

    // Edge case: if input is the size of the buffer, it's not null-terminated
    if (nameBuff[strlen(nameBuff) - 1] == '\n') {
        nameBuff[strlen(nameBuff) - 1] = '\0';
    }

    // Read an int from the console into a variable
    int age;
    printf("Enter your age: ");
    if (scanf("%d", &age) != 1) {
        fprintf(stderr, "Invalid input. Expected an integer.\n");
        return 1;
    }

    printf("Hello, %s! You are %d years old.\n", nameBuff, age);
}