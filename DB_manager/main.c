#include <stdio.h>
#include <stdlib.h>
#include "data_reader.h"

int main() {
    char * fileName;
    char* data;
    fileName = "/home/ouriel/Desktop/Bootcamp/checkPoint/School_DB_Project/Data/students_with_class.txt";

   
    data = readDataFromFile(fileName);
    if (data != NULL) {
        printf("Data read successfully\n");
        free(data);
    }

    return 0;
}