#include "school.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void InitializeSchool(struct School* school, char* data) {

    int i = 0;
    struct Student* node;
    char* dataLine;
    char* saveptr;  // This is required for strtok_r
    char* lineCopy = (char*)malloc(sizeof(char) * 200);

    dataLine = strtok_r(data, "\n", &saveptr);
    while (dataLine != NULL) {
        strncpy(lineCopy, dataLine, 200 - 1);
        node = createStudentFromString(lineCopy);

        if (school->students[node->level-1][node->classNumber-1] == NULL)
        {
            school->students[node->level-1][node->classNumber-1]= node;
        }
        else
        {
            struct Student* temp = school->students[node->level-1][node->classNumber-1];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;
        
        }
        dataLine = strtok_r(NULL, "\n", &saveptr);
    }
    free(lineCopy);
}

void deleteSchool(struct School school) {
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
                deleteLinkedList(school.students[i][j]);
            }
        }
    }
}

void printSchool(const struct School school){
    for (int i = 0; i < LEVELS; i++)
    {
        printf("Level %d\n", i);
        for (int j = 0; j < CLASSES; j++)
        {
            printf("Class %d\n", j);
            if (school.students[i][j] != NULL)
            {
                struct Student* temp = school.students[i][j];
                while (temp != NULL)
                {
                    printStudent(*temp);
                    temp = temp->next;
                }
            }
        }
    }

    
}

int addStudent(struct School* school, struct Student* student) {
    if (student->level > LEVELS || student->classNumber > CLASSES
        || student->level < 1 || student->classNumber < 1  )
    {
        printf("Invalid level or class\n");
        return 0;
    }
    if (student == NULL)
    {
        printf("Invalid student\n");
        return 0;
    }

    if (school->students[student->level-1][student->classNumber-1] == NULL)
    {
        school->students[student->level-1][student->classNumber-1] = student;
    }
    else
    {
        student->next = school->students[student->level-1][student->classNumber-1];
        school->students[student->level-1][student->classNumber-1] = student;
    }
    return 1;
}

int removeStudent(struct School* school, struct Student* student) {
    if (student == NULL)
    {
        printf("Invalid student\n");
        return 0;
    }
    if (school->students[student->level-1][student->classNumber-1] == NULL)
    {
        printf("No students in this class\n");
        deleteStudent(student);
        free(student);
        return 0;
    }
   
    if (school->students[student->level-1][student->classNumber-1] == student)
    {

        school->students[student->level-1][student->classNumber-1] = student->next;
        deleteStudent(student);
        free(student);
        student = NULL;
        return 1;
    }
    struct Student* temp = school->students[student->level-1][student->classNumber-1];
    while (temp->next != NULL)
    {
        if (temp->next == student)
        {
            temp->next = student->next;
            student->next = NULL;
            deleteLinkedList(student);
            return 1;
        }
        temp = temp->next;

    }
    temp = NULL;
    return 0;
}

struct Student* findStudentByName(const struct School school, const char* firstName, const char* lastName) {
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
                struct Student* temp = school.students[i][j];
                while (temp != NULL)
                {
                    if (strcmp(temp->firstName, firstName) == 0 && strcmp(temp->lastName, lastName) == 0)
                    {
                        return temp;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    return NULL;
}

struct Student* findStudentByPhone(const struct School school, const char* phoneNumber) {
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
                struct Student* temp = school.students[i][j];
                while (temp != NULL)
                {
                    if (strcmp(temp->phoneNumber, phoneNumber) == 0)
                    {
                        return temp;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    return NULL;
}

int gradeAverageByClass(const struct School school, int level, int classId){
    if (level > LEVELS || classId > CLASSES || level < 1 || classId < 1)
    {
        printf("Invalid level or class\n");
        return 0;
    }
    if (school.students[level-1][classId-1] == NULL)
    {
        printf("No students in this class\n");
        return 0;
    }
    int sum = 0;
    int count = 0;
    struct Student* temp = school.students[level-1][classId-1];
    while (temp != NULL)
    {
        sum += gradeAverage(*temp);
        count++;
        temp = temp->next;
    }
    if (count == 0)
    {
        printf("No students in this class\n");
        return 0;
    }
    return sum / count;
}

int exportSchool(const struct School school, const char* fileName){
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        return 1;
    }
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
                struct Student* temp = school.students[i][j];
                while (temp != NULL)
                {
                    fprintf(file, "%s %s %s %d %d ", temp->firstName, temp->lastName, temp->phoneNumber, temp->level, temp->classNumber);
                    for (int k = 0; k < MAX_COURSES; k++)
                    {
                        fprintf(file, "%d ", temp->scores[k]);
                    }
                    fprintf(file, "\n");
                    temp = temp->next;
                }
            }
        }
    }
    fclose(file);

    return 0;
}

struct Student* findUnderperformedStudents(struct School school, int minAverage)
{
    struct Student* underperformedStudents = NULL;
    struct Student* temp;
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (school.students[i][j] != NULL)
            {
                temp = school.students[i][j];
                while (temp != NULL)
                {
                    if (gradeAverage(*temp) < minAverage)
                    {
                        struct Student* node = copyStudent(temp);
                        node->next = underperformedStudents;
                        underperformedStudents = node;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    return underperformedStudents;
}

void findTopNStudentsPerCourse(const struct School school, int courseIndex, struct TopTenStudents* topTenStudents)
{
    struct School tempSchool;
    copySchool(&tempSchool, &school);
    struct Student* temp;
    int max=0;
    struct Student* maxStudent;
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            if (tempSchool.students[i][j] != NULL)
            {
                temp = tempSchool.students[i][j];
                max = temp->scores[courseIndex];
                maxStudent = temp;
                while (temp != NULL)
                {
                    if (temp->scores[courseIndex] > max)
                    {
                        max = temp->scores[courseIndex];
                        maxStudent = temp;
                    }
                    temp = temp->next;
                }
                temp = NULL;
                struct Student* node = copyStudent(maxStudent);
                node->next = topTenStudents->topStudents[i][j];
                topTenStudents->topStudents[i][j] = node;
                removeStudent(&tempSchool, maxStudent);
            }
        }
    }
    // free memory
    deleteSchool(tempSchool);

}


void copySchool(struct School* dest, const struct School* src)
{
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            dest->students[i][j] = NULL;
            if (src->students[i][j] != NULL)
            {
                struct Student* temp = src->students[i][j];
                while (temp != NULL)
                {
                    struct Student* node = copyStudent(temp);
                    addStudent(dest, node);
                    temp = temp->next;
                }
                temp = NULL;
            }
        }
    }

}
