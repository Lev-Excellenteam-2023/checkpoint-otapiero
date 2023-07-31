#pragma once
#include "student.h"

#define LEVELS 12
#define CLASSES 10
struct StudentNode
{
    struct Student student;
    int id;
    struct StudentNode *next;
};

struct StudentNode* createNode(struct Student student);


void deleteLinkedList(struct StudentNode* head);