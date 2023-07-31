#include "studentNode.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StudentNode* createNode(struct Student student) {
    struct StudentNode* node = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    node->student = student;
    node->next = NULL;
    return node;
}


    

void deleteLinkedList(struct StudentNode* node) {
    if (node == NULL)
    {
        return;
    }
    deleteLinkedList(node->next);
    free(node);
}
    
