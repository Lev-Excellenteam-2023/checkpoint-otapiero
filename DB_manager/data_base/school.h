#pragma once
#include "studentNode.h"

struct School
{
    struct StudentNode *students[12][10];

};
void IntilizeSchool(struct School school,char* data);

void deleteSchool(struct School school);
void printSchool(struct School school);