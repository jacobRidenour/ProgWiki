#ifndef BINARYIO_H
#define BINARYIO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

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
        for (size_t i = 0; i < numElements; i++) checksum += data[i];

        // the .bin will contain the header, then the data
        fwrite(&numElements, sizeof(uint32_t), 1, fp);
        fwrite(&checksum, sizeof(uint32_t), 1, fp);
        fwrite(data, sizeof(int32_t), numElements, fp);
    }
    else
    {
        // Unformatted binary data with un/printable and multibyte characters
        unsigned char message[] =
        {
            'a', 'l', 'o', 'n', 'e', ' ', 'i', 'n', ' ', 't', 'h', 'e', ' ', 'w', 'o', 'r', 'l', 'd', ' ',
            0x00, 0x01,  // nul / start of heading
            'i', 's', ' ', 'a', ' ', 'l', 'i', 't', 't', 'l', 'e', ' ',
            0x1B,        // escape
            0x7F,        // del
            'c', 'a', 't', 0x08, 'd', 'o', 'g', // backspace
            0xF0, 0x9F, 0x98, 0x80,  // 😀 emoji (4-byte UTF-8)
            0xF0, 0x9F, 0x90, 0xB1,  // 🐱 emoji (4-byte UTF-8)
            0xF0, 0x9F, 0x90, 0xB6   // 🐶 emoji (4-byte UTF-8)
        };

        fwrite(message, sizeof(char), sizeof(message), fp);
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

    unsigned char buffer[256];
    size_t bytesRead;
    
    while ((bytesRead = fread(buffer, sizeof(char), sizeof buffer, fp)) > 0)
    {
        printf("Data chunk: ");
        for (size_t i = 0; i < bytesRead; ++i)
        {
            size_t charLen = charlenUtf8(buffer[i]);

            if (charLen == 1)
            {
                if (isprint(buffer[i])) putchar(buffer[i]); // Printable ASCII
                else printf("\\x%02X", buffer[i]); // Non-printable, show hex
            }
            else if (charLen > 1 && i + charLen <= bytesRead)
            {
                // Likely a multibyte UTF-8 character; print as-is
                for (size_t j = 0; j < charLen; ++j) putchar(buffer[i + j]);
                i += charLen - 1;  // Move forward by char len
            }
            else printf("\\x%02X", buffer[i]); // Treat invalid bytes as hex
        }
        printf("\n");
    }

    if (ferror(fp)) perror("Error reading binary data\n");
    fclose(fp);
}

#endif /* BINARYIO_H */