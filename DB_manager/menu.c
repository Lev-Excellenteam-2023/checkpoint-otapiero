
#include <stdlib.h>

#include <stdio.h>

#include <string.h>
#include "menu.h"
#include "data_base/school.h"
#include "data_base/student.h"

enum menu_inputs
{

    Insert = '0',

    Delete = '1',

    Edit = '2',

    Search = '3',

    Showall = '4',

    Top10 = '5',

    UnderperformedStudents = '6',

    Average = '7',

    Export = '8',

    Exit = '9'

};
void menu(struct School *school)
{

    struct School *_school = school;
    char input;

    // school.name = "schoolName";

    do
    {

        printf("\n|School Manager<::>Home|\n");

        printf("--------------------------------------------------------------------------------\n");

        // printf("Welcome to ( %s ) School!\nYou have inserted ( %zu ) students.\n\n", school.name, school.numOfStudents);

        printf("\t[0] |--> Insert\n");

        printf("\t[1] |--> Delete\n");

        printf("\t[2] |--> Edit\n");

        printf("\t[3] |--> Search\n");

        printf("\t[4] |--> Show All\n");

        printf("\t[5] |--> Top 10 students per course\n");

        printf("\t[6] |--> Underperformed students\n");

        printf("\t[7] |--> Average per course\n");

        printf("\t[8] |--> Export\n");

        printf("\t[9] |--> Exit\n");

        printf("\n\tPlease Enter Your Choice (0-9): ");

        input = getc(stdin);

        fflush(stdin);

        getc(stdin);

        switch (input)
        {

        case Insert:
            insertNewStudent(_school);


            break;

        case Delete:
            deleteStudentOption(_school);

            break;

        case Edit:
            editStudentGrade(_school);

            break;

        case Search:
            searchStudent(_school);

            break;

        case Showall:
            printAllStudents(_school);


            break;

        case Top10:
            printTopNStudentsPerCourse(_school);

            break;

        case UnderperformedStudents:

            printUnderperformedStudents(_school);
            break;

        case Average:
            printAverage(_school);


            break;

        case Export:

            exportDatabase(_school);


            break;

        case Exit:

            // handleClosing();

            break;

        default:

            printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-10!\nPress any key to continue...", input);

            getc(stdin);

            getc(stdin);

            break;
        }
    } while (input != Exit);
}

void insertNewStudent(struct School *school)
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
    int level, classId;
    int *scores;
    do
    {
        printf("Enter student's first name: ");
        fgets(firstName, sizeof(firstName), stdin);
        firstName[strcspn(firstName, "\n")] = '\0'; // Remove trailing newline
    } while (nameValidetion(firstName) == 0);

    do
    {

        printf("Enter student's last name: ");
        fgets(lastName, sizeof(lastName), stdin);
        lastName[strcspn(lastName, "\n")] = '\0'; // Remove trailing newline
    } while (nameValidetion(lastName) == 0);

    do
    {
        printf("Enter student's phone number: ");
        fgets(phoneNumber, sizeof(phoneNumber), stdin);
        phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // Remove trailing newline
    } while (phoneValidetion(phoneNumber) == 0);

    printf("Enter student's level: ");
    level = readIntegerInput();

    printf("Enter student's class: ");
    classId = readIntegerInput();

    scores = (int *)malloc(sizeof(int) * MAX_COURSES);

    for (int i = 0; i < MAX_COURSES; i++)
    {
        printf("Enter student score in course %d: ", (i + 1));
        scanf("%d", &scores[i]);
    }

    struct Student *student = createStudent(firstName, lastName, phoneNumber, level, classId, scores);

    int result = addStudent(school, student);

    if (result == 1)
    {
        printf("Student added successfully\n");
    }
    else
    {
        printf("Failed to add student\n");
    }
    clearBuffer();
}
void deleteStudentOption(struct School *school)
{
    char phoneNumber[MAX_PHONE_LENGTH];
    size_t len = 0;
    do
    {
        printf("Enter student's phone number: ");
        len = get_input(phoneNumber, MAX_PHONE_LENGTH);
        if (len == MAX_PHONE_LENGTH )
        {
            printf("Too many characters,Press Enter to continue... \n");
            clearBuffer();
            phoneNumber[0] = 'a';
        }
    } while (phoneValidetion(phoneNumber) == 0);
    struct Student *student = findStudentByPhone(*school, phoneNumber);
    if (student == NULL)
    {
        printf("Student not found, failed to delete student\n");
        return;
    }
    int result = removeStudent(school, student);
    if (result == 1)
    {
        printf("Student deleted successfully\n");
        student = NULL;
    }
    else
    {
        printf("Failed to delete student\n");
    }
}
void editStudentGrade(const struct School *school)
{
    size_t len = 0;
    char phoneNumber[MAX_PHONE_LENGTH];
    do
    {
        printf("Enter student's phone number: ");
        len = get_input(phoneNumber, MAX_PHONE_LENGTH);
        if (len == MAX_PHONE_LENGTH )
        {
            printf("Too many characters, Press Enter to continue... \n");
            clearBuffer();
            phoneNumber[0] = 'a';
        }
    } while (phoneValidetion(phoneNumber) == 0);
    
    struct Student *student = findStudentByPhone(*school, phoneNumber);
    if (student == NULL)
    {
        printf("Student not found, failed to edit student\n");
        return;
    }
    int course;
    printf("Enter course number: ");
    course = readIntegerInput();
    if (course < 1 || course > 10)
    {
        printf("Invalid course number\n");
        return;
    }
    int grade;
    printf("Enter new grade: ");
    grade = readIntegerInput();
    if (grade < 0 || grade > 100)
    {
        printf("Invalid grade\n");
        return;
    }
    student->scores[course - 1] = grade;
    printf("Grade updated successfully\n");
    clearBuffer();
    
}

void searchStudent(const struct School *school)
{
    char phoneNumber[MAX_PHONE_LENGTH];
    size_t len = 0;
    do
    {
        printf("Enter student's phone number: ");
        len = get_input(phoneNumber, MAX_PHONE_LENGTH);
        if (len == MAX_PHONE_LENGTH )
        {
            printf("Too many characters, Press Enter to continue... \n");
            clearBuffer();
            phoneNumber[0] = 'a';
        }
    } while (phoneValidetion(phoneNumber) == 0);
    struct Student *student = findStudentByPhone(*school, phoneNumber);
    if (student == NULL)
    {
        printf("Student not found\n");
        return;
    }
    printf("Student found:\n");
    printStudent(*student);
}

void printAllStudents(const struct School *school)
{
    printSchool(*school);
}

void printAverage(const struct School *school)
{
    int level, classId;
    printf("Enter level: ");
    level = readIntegerInput();
    if (level < 1 || level > 12)
    {
        printf("Invalid level\n");
        return;
    }
    printf("Enter class: ");
    classId = readIntegerInput();
    if (classId < 1 || classId > 10)
    {
        printf("Invalid class\n");
        return;
    }
    int average = gradeAverageByClass(*school, level, classId);
    printf("Average grade for level %d class %d is %d\n", level, classId, average);
    clearBuffer();
}

void exportDatabase(const struct School *school)
{
    char fileName[100];
    printf("Enter file name: ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0'; // Remove trailing newline
    int result = exportSchool(*school, fileName);
    if (result == 0)
    {
        printf("School exported successfully\n");
    }
    else
    {
        printf("Failed to export school\n");
    }
}

void printUnderperformedStudents(const struct School *school)
{

    struct Student *underperformedStudents = findUnderperformedStudents(*school, MIN_AVRAGE);
    if (underperformedStudents == NULL)
    {
        printf("No underperformed students\n");
        return;
    }
    printf("Underperformed students:\n");
    struct Student *temp = underperformedStudents;
    while (temp != NULL)
    {
        printStudent(*temp);
        temp = temp->next;
    }
    deleteLinkedList(underperformedStudents);
}

void printTopNStudentsPerCourse(const struct School *school)
{
    int course;
    printf("Enter course number: ");
    course = readIntegerInput();
    
    while (course < 1 || course > 10)
    {
        printf("Invalid course number\n");
        course = readIntegerInput();
    }
    struct TopTenStudents topTenStudents;
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < CLASSES; j++)
        {
            topTenStudents.topStudents[i][j] = NULL;
        }
    }
    findTopNStudentsPerCourse(*school, course - 1, &topTenStudents);
    printf("Top 10 students in course %d:\n", course);
    for (int i = 0; i < LEVELS; i++)
    {
        if (topTenStudents.topStudents[i] == NULL)
        {
            break;
        }
        printf("Level %d:\n", i + 1);
        for (int j = 0; j < CLASSES; j++)
        {
            if (topTenStudents.topStudents[i][j] == NULL)
            {
                break;
            }
            struct Student *temp = topTenStudents.topStudents[i][j];
            while (temp != NULL)
            {
                printStudent(*temp);
                temp = temp->next;
            }
            temp = NULL;
        }
    }

    // Free memory
    for (int i = 0; i < LEVELS; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            deleteLinkedList(topTenStudents.topStudents[i][j]);
            topTenStudents.topStudents[i][j] = NULL;
        }
    }
    clearBuffer();
}

int readIntegerInput()
{
    int input;

    printf("Enter an integer: ");
    if (scanf("%d", &input) != 1)
    {
        // Invalid input, handle the error
        printf("Invalid input. Please enter an integer.\n");
        // Clear the input buffer to remove any leftover characters
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        // Ask for input again, or handle the error as needed
    }
    else
    {
        // Input is valid
        return input;
    }
}
int nameValidetion(const char *name)
{
    // check if the name is valid (only letters)
    int i = 0;
    while (name[i] != '\0')
    {
        if ((name[i] < 'a' || name[i] > 'z') && (name[i] < 'A' || name[i] > 'Z'))
        {
            printf("Invalid input. Please enter a name.\n");
            return 0;
        }
        i++;
    }
    return 1;
}


int phoneValidetion(const char *phone)
{
    // check if the phone number is valid (only numbers)
    int i = 0;
    while (phone[i] != '\0')
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            printf("Invalid input. Please enter a phone number.\n");
            return 0;
        }
        i++;
    }
    return 1;
}


/*

 * The function gets input from the user and ensures the input

 * doesn't exceed max_size. if yes - it will shrink it and will add \0.

 */

size_t get_input(char* dst, size_t max_size) {

    char* input = NULL;

    size_t len = 0;

    size_t len_size = 0;

    len_size = getline(&input, &len, stdin);

    if (len_size == -1)

        return -1;

    if (len_size < max_size) {

        input[len_size - 1] = '\0';

        strncpy(dst, input, len_size);

    }

    else {

        input[max_size - 1] = '\0';

        strncpy(dst, input, max_size);

        len_size = max_size;

    }

    free(input);

    return len_size;

}
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}


