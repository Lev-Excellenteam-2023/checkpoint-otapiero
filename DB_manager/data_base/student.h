#pragma once
#define MAX_COURSES 10



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

struct Student* createStudent(const char* firstName, const char* lastName, const char* phoneNumber, int level, int classId, int* scores);

struct Student* createStudentFromString(const char* data);

void deleteStudent(struct Student* student);
void printStudent(const struct Student student);

void deleteLinkedList(struct Student* head);

int gradeAverage(const struct Student student);
struct Student* copyStudent(const struct Student* student);
int * copyScores(int* scores);


