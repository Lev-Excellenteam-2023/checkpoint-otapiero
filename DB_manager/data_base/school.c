#include "school.h"
#include "studentNode.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void IntilizeSchool(struct School school, char* data) {
    int i = 0;
    struct StudentNode* node;
    struct Student tempStudent;
    char* dataLine;
    char* saveptr;  // This is required for strtok_r
    char* lineCopy = (char*)malloc(sizeof(char) * 200);

    dataLine = strtok_r(data, "\n", &saveptr);
    while (dataLine != NULL) {
        strncpy(lineCopy, dataLine, 200 - 1);
        tempStudent = createStudentFromString(lineCopy);

        node = createNode(tempStudent);
        node->next = school.students[tempStudent.level-1][tempStudent.classNumber-1];
        i++;
        dataLine = strtok_r(NULL, "\n", &saveptr);
    }
    free(lineCopy);
    printf("School intilized successfully\n");
}

void deleteSchool(struct School school) {
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
               deleteLinkedList(school.students[i][j]);
            }
        }
    }
}

void printSchool(struct School school){
    for (int i = 0; i < LEVELS; i++)
    {
        printf("Level %d\n", i);
        for (int j = 0; j < CLASSES; j++)
        {
            printf("Class %d\n", j);
            if (school.students[i][j] != NULL)
            {
                struct StudentNode* temp = school.students[i][j];
                while (temp != NULL)
                {
                    printStudent(temp->student);
                    temp = temp->next;
                }
            }
        }
    }

    
}