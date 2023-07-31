#pragma once

struct Student
{
    char firstName[20];
    char lastName[20];
    char phoneNumber[20];
    int level;
    int classNumber;
    int *scores;
    
};

struct Student createStudent(char* firstName, char* lastName, char* phonNumber, int level, int classId, int* scores);

struct Student createStudentFromString(const char* data);

void deleteStudent(struct Student* student);
void printStudent(struct Student student);

