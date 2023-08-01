#include "school.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void InitializeSchool(struct School* school, char* data) {

    int i = 0;
    struct Student* node;
    char* dataLine;
    char* saveptr;  // This is required for strtok_r
    char* lineCopy = (char*)malloc(sizeof(char) * 200);

    dataLine = strtok_r(data, "\n", &saveptr);
    while (dataLine != NULL) {
        strncpy(lineCopy, dataLine, 200 - 1);
        node = createStudentFromString(lineCopy);

        if (school->students[node->level-1][node->classNumber-1] == NULL)
        {
            school->students[node->level-1][node->classNumber-1]= node;
        }
        else
        {
            struct Student* temp = school->students[node->level-1][node->classNumber-1];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;
        
        }
        dataLine = strtok_r(NULL, "\n", &saveptr);
    }
    free(lineCopy);
}

void deleteSchool(struct School school) {
    printf("Deleting school\n");
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

void printSchool(const struct School school){
    for (int i = 0; i < LEVELS; i++)
    {
        printf("Level %d\n", i);
        for (int j = 0; j < CLASSES; j++)
        {
            printf("Class %d\n", j);
            if (school.students[i][j] != NULL)
            {
                struct Student* temp = school.students[i][j];
                while (temp != NULL)
                {
                    printStudent(*temp);
                    temp = temp->next;
                }
            }
        }
    }

    
}