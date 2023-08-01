#pragma once
#include "student.h"




#define LEVELS 12
#define CLASSES 10
#define MAX_NAME_LENGTH 20
#define MAX_PHONE_LENGTH 20


struct School
{
    struct Student* students[LEVELS][CLASSES];

};
struct TopTenStudents
{
    struct Student * topStudents[LEVELS][10];
};
void InitializeSchool(struct School* school,char* data);

void deleteSchool(struct School school);
void printSchool(const struct School school);
int addStudent(struct School* school, struct Student* student);
int removeStudent(struct School* school, struct Student* student);
struct Student* findStudentByName(const struct School school, const char* firstName, const char* lastName);
struct Student* findStudentByPhone(const struct School school, const char* phoneNumber);
void copySchool(struct School* dest, const struct School* src);
int gradeAverageByClass(const struct School school, int level, int classId);
int exportSchool(const struct School school, const char* fileName);
struct Student* findUnderperformedStudents(struct School school, int minAverage);

void findTopNStudentsPerCourse(const struct School school, int courseIndex, struct TopTenStudents* topTenStudents);
void copySchool(struct School* dest, const struct School* src);

