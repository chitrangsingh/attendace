#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 50
#define FILENAME "attendance.csv"

typedef struct Student
{
    char name[MAX_NAME_LENGTH];
    int present;
} Student;

void printMenu()
{
    printf("School Attendance\n");
    printf("-----------------\n");
    printf("1. Add student\n");
    printf("2. Take attendance\n");
    printf("3. View attendance report\n");
    printf("4. Exit\n");
}

void addStudent(Student students[], int *num_students)
{
    if (*num_students >= MAX_STUDENTS)
    {
        printf("Error: Maximum number of students reached.\n");
        return;
    }

    printf("Enter student name: ");
    char name[MAX_NAME_LENGTH];
    scanf("%s", name);

    Student student;
    strcpy(student.name, name);
    student.present = 0;

    students[*num_students] = student;
    (*num_students)++;

    printf("Student added successfully.\n");
}

void takeAttendance(Student students[], int num_students)
{
    printf("Mark attendance:\n");
    for (int i = 0; i < num_students; i++)
    {
        printf("%d. %s (1 for present / 0 for absent): ", i + 1, students[i].name);
        scanf("%d", &students[i].present);
    }
    printf("Attendance taken successfully.\n");
}

void viewAttendance(Student students[], int num_students)
{
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    fprintf(fp, "Name,Attendance\n");
    for (int i = 0; i < num_students; i++)
    {
        fprintf(fp, "%s,%d\n", students[i].name, students[i].present);
    }

    fclose(fp);

    printf("Attendance report saved to file.\n");
}

void loadAttendance(Student students[], int *num_students)
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    char line[MAX_NAME_LENGTH + 10]; // account for comma and newline
    fgets(line, sizeof(line), fp);   // skip header row

    while (fgets(line, sizeof(line), fp))
    {
        char name[MAX_NAME_LENGTH];
        int present;

        sscanf(line, "%[^,],%d", name, &present);

        Student student;
        strcpy(student.name, name);
        student.present = present;

        students[*num_students] = student;
        (*num_students)++;
    }

    fclose(fp);

    printf("Attendance records loaded successfully.\n");
}

int main()
{
    Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice = 0;

    loadAttendance(students, &num_students);

    while (choice != 4)
    {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            addStudent(students, &num_students);
            break;

        case 2:
            takeAttendance(students, num_students);
            break;

        case 3:
            viewAttendance(students, num_students);
            break;

        case 4:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        printf("\n");
    }

    // save attendance records to file
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open file for writing.\n");
        return 1;
    }

    fprintf(fp, "Name,Attendance\n");
    for (int i = 0; i < num_students; i++)
    {
        fprintf(fp, "%s,%d\n", students[i].name, students[i].present);
    }

    fclose(fp);

    return 0;
}