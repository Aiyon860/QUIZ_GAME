#include <stdio.h>

#define NUM_STUDENTS 5
#define NAME_LENGTH 50
#define PASSING_SCORE 70

typedef struct {
    char name[NAME_LENGTH];
    int score;
} Student;

void printDashboard(Student students[], int size) 
{
    printf("+-----------------------------+--------+---------+\n");
    printf("| %-27s | %-6s | %-6s |\n", "Student Name", "Score", "Passing");
    printf("+-----------------------------+--------+---------+\n");

    for (int i = 0; i < size; i++) {
        printf("| %-27s | %-6d | %-6s %s|\n", students[i].name, students[i].score, students[i].score >= PASSING_SCORE ? "Yes" : "No", " ");
    }

    printf("+-----------------------------+--------+---------+\n");
}

int main() {
    Student students[NUM_STUDENTS] = {
        {"Alice Johnson", 85},
        {"Bob Smith", 92},
        {"Charlie Brown", 78},
        {"Diana Prince", 88},
        {"Evan Lee", 91}
    };

    printDashboard(students, NUM_STUDENTS);

    return 0;
}
