/* 
 * Nama: Daniel Adi Pratama
 * NIM: 4.33.23.0.07
 * Kelas: TI-1A
 * Mata Kuliah: Struktur Data
 * Dosen: Eri Eli Lavindi, M.Kom.
 * Judul Projek TuBes: QUIZ GAME
 * File: main.c
 */

// Preprocessor
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "../utils/menu/print_collections.h"
#include "../utils/quiz_related/timer.h"

#define NAME_LEN 256
#define MAX_LINE_LENGTH 256
#define MAX_QUESTIONS 1024
#define NAME_LENGTH 50
#define PASSING_SCORE 150
#define NUM_STUDENTS 10

// Enum Declaration
typedef enum level {
  EASY,
  MEDIUM,
  HARD,
} Level;

char level_str[3][8] = { "EASY\n", "MEDIUM\n", "HARD\n" };

// Struct Declarations
typedef struct student {
  char name[NAME_LEN];
  int score;
} Student;

typedef struct node Question;
typedef struct node {
  char text[MAX_LINE_LENGTH * 6];
  Level difficulty;
  Question *next;
} Question;

typedef struct linked_list {
  Question *head;
} QuestionList;

// Functions Declaration
void start_program();
void end_program();
void show_menu();
void show_result();
int randomize();
void play_quiz();
void open_guide_book();
Student create_student(Student students[]);
void open_report_results();
void print_dashboard(Student students[], int size);
void show_question();
void read_questions(FILE *file, QuestionList **q_list, Level q_diff);
Question *create_node(char *q_text, Level q_diff);
void insert_at_end(QuestionList **q_list, char *q_text, Level q_diff);
void insert_at_end_ALL(QuestionList **q_all, QuestionList **q_src, int q_num_from_src);

// Students List
Student Students[NUM_STUDENTS];

// Main Entry Point
int main()
{
  start_program();
  return EXIT_SUCCESS;
}

// Functions Definition
void start_program()
{
  show_menu();
}

void end_program()
{
  Sleep(3000);
  system("cls");
  exit(EXIT_SUCCESS);
}

void show_menu()
{
  char choice;
  while (true)
  {
    system("cls");
    print_header();
    scanf("%c", &choice);
    fflush(stdin);

    switch (toupper(choice))
    {
      case 'A':
        system("cls");
        play_quiz();
        break;
      case 'B':
        system("cls");
        open_guide_book();
        break;
      case 'C':
        system("cls");
        open_report_results();
        break;
      case 'Q':
        printf("\n\n\t\t\t\t\t\t\tTerimakasih Sudah Mengerjakan Kuis ini, \n\t\t\t\t\tKami berharap Kuis yang kami berikan dapat bermanfaat bagi banyak orang!\n");
        end_program();
      default:
        fprintf(stderr, "Input Tidak Dimengerti. Silahkan Coba Kembali!\n");
    }
  }
}

void play_quiz()
{
  FILE *file;

  QuestionList *EASY_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList)); 
  EASY_QUIZ->head = NULL;
  file = fopen("../docs/quiz_related/questions/1_beginner.txt", "r");
  read_questions(file, &EASY_QUIZ, EASY);
  fclose(file);

  QuestionList *MEDIUM_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList)); 
  MEDIUM_QUIZ->head = NULL;
  file = fopen("../docs/quiz_related/questions/2_intermediate.txt", "r");
  read_questions(file, &MEDIUM_QUIZ, MEDIUM);
  fclose(file);

  QuestionList *HARD_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList));
  HARD_QUIZ->head = NULL;
  file = fopen("../docs/quiz_related/questions/3_advanced.txt", "r");
  read_questions(file, &HARD_QUIZ, HARD);
  fclose(file);

  // That will be used in real quiz program 
  QuestionList *ALL = (QuestionList *)calloc(1, sizeof(QuestionList)); 
  ALL->head = NULL;

  /* 
     Inserting all different range of difficulties of questions 
     into the main questions list to be displayed to the user 
  */
  for (int i = 0; i < 10; i++)
  {
    Sleep(1000);
    if (i < 3)
      insert_at_end_ALL(&ALL, &EASY_QUIZ, randomize());
    else if (i < 6)
      insert_at_end_ALL(&ALL, &MEDIUM_QUIZ, randomize());
    else
      insert_at_end_ALL(&ALL, &HARD_QUIZ, randomize());
  }

  Question* temp = ALL->head;
  while (temp != NULL)
  {
    printf("%s\n", temp->text);
    temp = temp->next;
  }

  print_pause();
}

void show_result()
{
  // print_dashboard();
  print_pause();
}

void open_guide_book()
{
  FILE *file = fopen("../docs/guidebook/help.txt", "r");
  if (file == NULL) 
  {
    fprintf(stderr, "Failed to open file");
    return;
  }

  // Seek to the end of the file to get the size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET); // Go back to the beginning of the file

  // Allocate memory to hold the file content plus a null terminator
  char *buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) 
  {
    fprintf(stderr, "Failed to allocate memory");
    fclose(file);
    return;
  }

  // Read the file content into the buffer
  size_t bytesRead = fread(buffer, 1, fileSize, file);

  // Null-terminate the buffer
  buffer[bytesRead] = '\0';

  // Loop the menu
  bool isLoop = true;
  while (isLoop) 
  {
    system("cls");
    printf("%s\n", buffer);
    isLoop = print_pause();
  }

  // Free the allocated memory and close the file
  free(buffer);
  fclose(file);
}

void open_report_results()
{
  print_dashboard(Students, NUM_STUDENTS);
  
}

void show_question()
{

}

void read_questions(FILE *file, QuestionList **q_list, Level q_diff)
{
  char line[MAX_LINE_LENGTH], full_text[MAX_QUESTIONS];
  int q_index = -1, count = 0;

  while (fgets(line, sizeof(line), file)) 
  {
    // Remove trailing newline character
    line[strcspn(line, "\n")] = '\0';

    // Check if the line is a question
    if (line[0] >= '0' && line[0] <= '9') 
    {
      q_index++;
      strcpy(full_text, level_str[q_diff]);
      strcat(full_text, line);
      strcat(full_text, "\n"); // Add newline for formatting
    } 
    else if (line[0] >= 'a' && line[0] <= 'd' && line[1] == ')') 
    {
      strcat(full_text, line);
      strcat(full_text, "\n"); // Add newline for formatting
      count++;
    }

    if (count == 4)
    {
      full_text[strlen(full_text)] = '\0';
      insert_at_end(q_list, full_text, q_diff);
      count = 0;
      full_text[0] = '\0';
    }
  }
}

Question *create_node(char *q_text, Level q_diff)
{
  Question *new_node = (Question *)calloc(1, sizeof(Question));
  strcpy(new_node->text, q_text);
  new_node->difficulty = q_diff;
  new_node->next = NULL;
  return new_node;
}

void insert_at_end(QuestionList **q_list, char *q_text, Level q_diff)
{
  Question *new_node = create_node(q_text, q_diff);
  if ((*q_list)->head == NULL)
  {
    (*q_list)->head = new_node;
    return;
  }

  // Traverse the list if q_list is not NULL
  Question *temp = (*q_list)->head;
  while (temp->next != NULL)
    temp = temp->next;
  temp->next = new_node;
}

void insert_at_end_ALL(QuestionList **q_all, QuestionList **q_src, int q_num_from_src)
{
  Question *temp_src = (*q_src)->head;
  for (int i = 0; i < q_num_from_src; i++)
    temp_src = temp_src->next;

  if ((*q_all)->head == NULL)
  {
    (*q_all)->head = temp_src;
    return;
  }

  // // Traverse the list if q_all is not NULL
  // Question *temp_all = (*q_all)->head;
  // while (temp_all->next != NULL)
  //   temp_all = temp_all->next;
  // temp_all->next = temp_src;
}

void print_dashboard(Student students[], int size) 
{
  printf("+-----------------------------+--------+---------+\n");
  printf("| %-27s | %-6s | %-6s |\n", "Student Name", "Score", "Passing");
  printf("+-----------------------------+--------+---------+\n");

  for (int i = 0; i < size; i++) 
  {
    printf("| %-27s | %-6d | %-6s %s|\n", students[i].name, students[i].score, students[i].score >= PASSING_SCORE ? "Yes" : "No", " ");
  }

  printf("+-----------------------------+--------+---------+\n");
}

// Student create_student(Student student[])
// {
//   return (Student) { .name = "NULL", .score = 0 };
// }
