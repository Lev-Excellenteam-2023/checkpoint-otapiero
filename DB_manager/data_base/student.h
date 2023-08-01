#pragma once


#define LEVELS 12
#define CLASSES 10

struct Student
{
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    int level;
    int classNumber;
    int *scores;

    struct Student *next;
};

struct Student* createStudent(char* firstName, char* lastName, char* phoneNumber, int level, int classId, int* scores);

struct Student* createStudentFromString(const char* data);

void deleteStudent(struct Student* student);
void printStudent(const struct Student student);

void deleteLinkedList(struct Student* head);

