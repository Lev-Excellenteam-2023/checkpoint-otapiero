#include <stdio.h>
#include <stdlib.h>
#include "data_reader.h"
#include "data_base/student.h"
#include "data_base/studentNode.h"
#include "data_base/school.h"

int main() {
    char * fileName;
    char* data;
    fileName = "/home/ouriel/Desktop/Bootcamp/checkPoint/School_DB_Project/Data/students_with_class.txt";

   
    data = readDataFromFile(fileName);
    if (data != NULL) {
        printf("Data read successfully\n");
    }
    struct School school;
    IntilizeSchool(school, data);
    deleteSchool(school);
    printf("School deleted successfully\n");
    free(data);




    return 0;
}