#include "data_reader.h"
#include <stdio.h>
#include <stdlib.h>

// Read the data from the file and return the data

char* readDataFromFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File not found");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* data = (char*)malloc(sizeof(char) * fileSize);
    fread(data, sizeof(char), fileSize, file);
    fclose(file);

    return data;

}
