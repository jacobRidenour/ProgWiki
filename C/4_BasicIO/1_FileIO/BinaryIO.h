#ifndef BINARYIO_H
#define BINARYIO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

/******************************************************************************
* BinaryIO.h
*
* Basic binary file IO. Create un/formatted files and parse them.
*
******************************************************************************/

void readFormattedBinary();
void readUnformattedBinary();
void createBinaryFile(bool formatted);

void createBinaryFile(bool formatted)
{
    // the "b" is generally not needed on linux
    // but is almost always needed on Windows.
    FILE* fp = fopen("data.bin", "wb");
    if (fp == NULL)
    {
        perror("Error opening binary file for writing\n");
        return;
    }

    if (formatted)
    {
        int32_t data[] = {123, 456, 789, 101112, 131415};
        
        // Add a header to the beginning of the file so
        // the reader knows how to parse it;
        // (# elements, checksum)
        uint32_t numElements = sizeof data / sizeof data[0];

        // Very simple checksum
        uint32_t checksum = 0;
        for (size_t i = 0; i < numElements; i++) {
            checksum += data[i];
        }

        // the .bin will contain the header, then the data
        fwrite(&numElements, sizeof(uint32_t), 1, fp);
        fwrite(&checksum, sizeof(uint32_t), 1, fp);
        fwrite(data, sizeof(int32_t), numElements, fp);
    }
    else
    {
        char message[] = "alone in the world isalittlecatdog";
        fwrite(message, sizeof(char), strlen(message), fp);
    }

    fclose(fp);
}

void readFormattedBinary()
{
    createBinaryFile(true);

    FILE* fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        perror("Error opening binary file for reading\n");
        return;
    }

    uint32_t numElements, checksum, computedChecksum = 0;

    // We're using some prescribed format: 
    // header (number of elements, checksum), then data
    if (fread(&numElements, sizeof(uint32_t), 1, fp) != 1
    || fread(&checksum, sizeof(uint32_t), 1, fp) != 1)
    {
        perror("Error reading header\n");
        fclose(fp);
        return;
    }
    printf("\nAttempting to read formatted .bin file\n");
    printf("======================================\n");

    // Allocate buffer based on numElements
    int32_t* buffer = malloc(numElements * sizeof(int32_t));
    if (buffer == NULL)
    {
        perror("Couldn't allocate memory for data buffer\n");
        fclose(fp);
        return;
    }

    printf("Reading data from binary file with header:\n");
    if (fread(buffer, sizeof(int32_t), numElements, fp) != numElements)
    {
        perror("Error reading data from binary file\n");
    }
    else
    {
        // Validate we've read the data in correctly /
        // no corruption by verifying the checksum
        for (size_t i = 0; i < numElements; ++i)
        {
            computedChecksum += buffer[i];
            printf("Data %zu: %d\n", i + 1, buffer[i]);
        }

        // Verify checksum
        if (checksum == computedChecksum) printf("Checksum validated: %u\n", checksum);
        else printf("Checksum error: expected %u, got %u\n", checksum, computedChecksum);
    }

    free(buffer);
    fclose(fp);
}

void readUnformattedBinary()
{
    createBinaryFile(false);

    FILE* fp = fopen("data.bin", "rb");
    if (fp == NULL)
    {
        perror("Error opening binary file for reading\n");
        return;
    }
    printf("\nAttempting to read unformatted .bin file\n");
    printf("========================================\n");

    // Flexible buffer size based on the initial read
    char buffer[256];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(char), sizeof buffer - 1, fp)) > 0)
    {
        buffer[bytesRead] = '\0';  // Null-terminate for safe string printing
        printf("Data chunk: %s\n", buffer);

        // Example of handling unknown binary format:
        // For each byte, check if it's printable; if not, show it in hexadecimal.
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] >= 32 && buffer[i] <= 126)
            {
                putchar(buffer[i]);
            }
            else
            {
                printf("\\x%02X", (unsigned char)buffer[i]);
            }
        }
        printf("\n");
    }

    if (ferror(fp)) perror("Error reading binary data\n");
    fclose(fp);
}

#endif /* BINARYIO_H */