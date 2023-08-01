#pragma once
#include "data_base/school.h"

#define MAX_NAME_LENGTH 20
#define MAX_PHONE_LENGTH 20
#define MAX_COURSES 10
#define MIN_AVRAGE 60
void menu(struct School *school);

void insertNewStudent(struct School* school);
void deleteStudentOption(struct School* school);
void editStudentGrade(const struct School* school);
void searchStudent(const struct School * school);
void printAllStudents(const struct School* school);
void printAverage(const struct School* school);
void exportDatabase(const struct School* school);
void printUnderperformedStudents(const struct School* school);
void printTopNStudentsPerCourse(const struct School* school);
int readIntegerInput();
int nameValidetion(const char * name);
int phoneValidetion(const char * phone);

