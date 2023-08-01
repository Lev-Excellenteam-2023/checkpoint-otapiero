#pragma once
#include "student.h"

struct School
{
    struct Student* students[12][10];

};
void IntilizeSchool(struct School school,char* data);

void deleteSchool(struct School school);
void printSchool(const struct School school);