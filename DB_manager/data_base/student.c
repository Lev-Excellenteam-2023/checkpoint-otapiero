#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student* createStudent(const char* firstName, const char* lastName, const char* phoneNumber, int level , int classId, int* scores) {
    struct Student* student;

    student = (struct Student*)malloc(sizeof(struct Student));
    student->level = level;
    student->classNumber = classId;
    student->scores = scores;
    strncpy(student->firstName, firstName, sizeof(student->firstName) - 1);

    strncpy(student->lastName, lastName, sizeof(student->lastName) - 1);
    strncpy(student->phoneNumber, phoneNumber, sizeof(student->phoneNumber) - 1);
    student->firstName[sizeof(student->firstName) - 1] = '\0';
    student->lastName[sizeof(student->lastName) - 1] = '\0';
    student->phoneNumber[sizeof(student->phoneNumber) - 1] = '\0';
    student->next = NULL;


    return student;

} 

struct Student* createStudentFromString(const char* data) {

    struct Student* student;
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    int level, classId;
    int* scores;
    char dataCopy[200];
    strncpy(dataCopy, data, sizeof(dataCopy) - 1);
    strncpy(firstName, strtok(dataCopy, " "), sizeof(firstName) - 1);
    strncpy(lastName, strtok(NULL, " "), sizeof(lastName) - 1);
    strncpy(phoneNumber, strtok(NULL, " "), sizeof(phoneNumber) - 1);

    level = atoi(strtok(NULL, " "));
    classId = atoi(strtok(NULL, " "));
    scores = (int*)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        scores[i] = atoi(strtok(NULL, " "));
    }

    student = createStudent(firstName, lastName, phoneNumber , level, classId, scores);

    return student; 
}


void deleteStudent(struct Student* student) {
    if (student == NULL) {
        return;
    }

    free(student->scores);

    student->scores = NULL;
}

void printStudent(const struct Student student)
{
    printf("Student name: %s %s\n", student.firstName, student.lastName);
    printf("Student phone number: %s\n", student.phoneNumber);
    printf("Student level: %d\n", student.level);
    printf("Student class: %d\n", student.classNumber);
    printf("Student scores: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", student.scores[i]);
    }
}

void deleteLinkedList(struct Student* node) {
    if (node == NULL)
    {
        return;
    }

    deleteLinkedList(node->next);
    deleteStudent(node);
    free(node);
    node = NULL;
}

int gradeAverage(const struct Student student) {
    int sum = 0;
    for (int i = 0; i < MAX_COURSES; i++)
    {
        sum += student.scores[i];
    }
    return sum / MAX_COURSES;
}

struct Student* copyStudent(const struct Student* student) {
    struct Student* copy = createStudent(student->firstName, student->lastName, student->phoneNumber, student->level, 
     student->classNumber, copyScores(student->scores));

    return copy;
}
    
int * copyScores(int* scores) {
    int* copy = (int*)malloc(sizeof(int) * MAX_COURSES);
    for (int i = 0; i < MAX_COURSES; i++)
    {
        copy[i] = scores[i];
    }
    return copy;
}