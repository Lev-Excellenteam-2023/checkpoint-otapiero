#include <stdio.h>
#include <stdlib.h>
#include "data_reader.h"
#include "data_base/student.h"
#include "data_base/school.h"
#include "menu.h"  
#include "encryption.h"

int main() {
    char * fileName;
    char* data;
    fileName = "/home/ouriel/Desktop/Bootcamp/checkPoint/School_DB_Project/Data/students_with_class.txt";
    

   
    data = readDataFromFile(fileName);
    if (data != NULL) {
        printf("Data read successfully\n");
    }
    struct School school;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            school.students[i][j] = NULL;
        }   
    }
    InitializeSchool(&school, data);
    //encrypt_to_file(data, KEY, IV, "encrypted.txt");
    //printf("Data encrypted successfully\n");
    //decrypt_from_file("encrypted.txt", "decrypted.txt", KEY, IV, data);
    //printf("Data decrypted successfully\n");
    printf("school initialized successfully\n");
    menu(&school);
    deleteSchool(school);
    printf("School deleted successfully\n");
    free(data);




    return 0;
}