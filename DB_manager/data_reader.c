#include "data_reader.h"
#include <stdio.h>
#include <stdlib.h>

// Read the data from the file and return the data

   char* readDataFromFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File not found\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* data = (char*)malloc(sizeof(char) * (fileSize + 1)); // +1 for null terminator
    if (data == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(data, sizeof(char), fileSize, file);
    data[fileSize] = '\0'; // Null-terminate the string
    fclose(file);

    return data;
}
