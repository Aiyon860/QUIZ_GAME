/* 
 * Nama: Daniel Adi Pratama
 * NIM: 4.33.23.0.07
 * Kelas: TI-1A
 * Mata Kuliah: Struktur Data
 * Dosen: Eri Eli Lavindi, M.Kom.
 * Judul Projek TuBes: QUIZ GAME
 * File: main.c
 */

/* Preprocessor */
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <windows.h>
#include "../utils/menu/print_collections.h"
#include "../utils/quiz_related/timer.h"

#define NAME_LEN 25
#define MAX_LINE_LENGTH 256
#define MAX_QUESTIONS 1024
#define NAME_LENGTH 50
#define PASSING_SCORE 150
#define NUM_STUDENTS 10

/* Enum Declaration */
typedef enum level {
  EASY,
  MEDIUM,
  HARD,
} Level;

char level_str[3][8] = { "EASY\n", "MEDIUM\n", "HARD\n" };

/* Struct Declarations */
typedef struct student {
  char name[NAME_LEN];
  int score;
  int rate_score;
} Student;

typedef struct node Question;
typedef struct node {
  int number;
  char text[MAX_LINE_LENGTH * 6];
  Level difficulty;
  char answer;
  Question *next;
} Question;

typedef struct linked_list {
  Question *head;
} QuestionList;

typedef struct answer_node AnswerNode;
typedef struct answer_node {
  int question_index;
  char student_answer;
  int score_achieved;
  AnswerNode *next;
} AnswerNode;

/* Functions Declaration */
// Menu
void start_program();
void end_program();
void show_menu();
void open_guide_book();
void play_quiz(Student students[], int student_index);
void show_final_result(AnswerNode **top_ref);
void open_report(Student *students);
void print_dashboard(Student students[], int size);
void create_student(Student students[], int *student_index);
void show_pass_result(const int final_score);
void show_fail_result(const int final_score);
void correct_result_display();
void wrong_result_display(char student_ans, char correct_ans, char *reason);
void remove_all_students(int *num_students);
void remove_one_student(Student student[], int *num_students, int student_index, bool *is_valid);

// Logic
void show_questions(Student students, QuestionList *ques_all, AnswerNode **top_ref);
void read_question(FILE *question, FILE *answer, QuestionList **q_list, Level q_diff);
Question *create_question_node(char *q_text, Level q_diff, int number, char answer);
void insert_at_end(QuestionList **q_list, char *q_text, Level q_diff, int number, char answer);
void insert_at_end_ALL(QuestionList **q_all, QuestionList *q_src, int q_num_from_src);
char read_answer(FILE *file, int number);
AnswerNode *create_answer_node(int q_index, char student_ans, int score_achieved);
void push_answer(AnswerNode **top_ref, int q_index, char student_ans, int score_achieved);
AnswerNode *pop_answer(AnswerNode **top_ref);
int calculate_score(AnswerNode **top_ref);

/* Main Entry Point */
int main()
{
  start_program();
  return EXIT_SUCCESS;
}

// Functions Definition
void start_program() { show_menu(); }

void end_program()
{
  Sleep(3000);
  system("cls");
  exit(EXIT_SUCCESS);
}

void show_menu()
{
  char choice;
  Student STUDENTS[NUM_STUDENTS] = {0};
  int num_students = 0;

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
        create_student(STUDENTS, &num_students);
        system("cls");
        play_quiz(STUDENTS, num_students);
        num_students++;
        break;
      case 'B':
        system("cls");
        open_guide_book();
        break;
      case 'C':
        system("cls");
        open_report(STUDENTS);
        break;
      case 'Q':
        printf("\n\n\t\t\t\t\t\t\tTerimakasih Sudah Mengerjakan Kuis ini, \n\t\t\t\t\tKami berharap Kuis yang kami berikan dapat bermanfaat bagi banyak orang!\n");
        end_program();
      default:
        fprintf(stderr, "Input Tidak Dimengerti. Silahkan Coba Kembali dalam 3 Detik!\n");
        Sleep(3000);
    }
  }
}

void create_student(Student students[], int *num_students)
{
  if (*num_students >= NUM_STUDENTS)
  {
    char choice;
    bool is_valid_input = false;
    printf("Maaf, tidak bisa menambah profile baru karena list nama di report sudah penuh!\n");
    while (true)
    {
      printf("Apakah anda ingin menghapus terlebih dahulu salah satu data (A) atau menghapus semua data (B) ?");
      printf("Pilih: ");
      scanf("%c", &choice);
      switch (toupper(choice))
      {
        case 'A':
          while (true)
          {
            int choice_index;
            bool is_valid;
            printf("Ingin menghapus data dengan nomer berapa?");
            scanf("%d", &choice_index);
            remove_one_student(students, num_students, choice_index, &is_valid);
            if (is_valid) break;
            system("cls");
          }
          is_valid_input = true;
          break;
        case 'B':
          remove_all_students(num_students);
          is_valid_input = true;
          break;
        default:
          fprintf(stderr, "Input Tidak Dimengerti. Silahkan Coba Kembali dalam 3 Detik!\n");
          Sleep(3000);
          system("cls");
      }
      if (is_valid_input) break;
    }
  }

  while (true)
  {
    printf("Silahkan masukkan nama Anda (Maks. 20 huruf): ");
    fgets(students[*num_students].name, sizeof(students[*num_students].name), stdin);
    students[*num_students].name[strcspn(students[*num_students].name, "\n")] = '\0';
    fflush(stdin);

    int len = strlen(students[*num_students].name);
    if (len <= 20) break;
    else
    {
      fprintf(stderr, "Error: nama mengandung lebih dari 20 karakter, Silahkan coba kembali dalam 5 detik!\n");
      Sleep(5000);
    }
  }

  students[*num_students].score = 0;
  students[*num_students].rate_score = 1;

  printf("Tunggu 5 detik untuk memulai kuis....");
  Sleep(5000);
}

void remove_one_student(Student student[], int *num_students, int student_index, bool *is_valid)
{
  if (student_index < 0 || student_index >= NUM_STUDENTS)
  {
    printf("Tidak ada data dengan index %d.\n", student_index);
    printf("(Menunggu 3 detik untuk melanjutkan program....)");
    Sleep(3000);
    *is_valid = false;
    return;
  }

  for (int i = student_index; i < *num_students - 1; ++i)
    student[i] = student[i + 1];

  (*num_students)--;
  *is_valid = true;
}

void remove_all_students(int *num_students)
{
  *num_students = 0;
}

void play_quiz(Student students[], int student_index)
{
  AnswerNode *ANSWER_STACK = NULL;

  FILE *question, *answer;

  QuestionList *EASY_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList)); 
  EASY_QUIZ->head = NULL;
  question = fopen("../docs/quiz_related/questions/1_beginner.txt", "r");
  answer = fopen("../docs/quiz_related/answers/1_beginner.txt", "r"); 
  read_question(question, answer, &EASY_QUIZ, EASY);
  fclose(question);
  fclose(answer);

  QuestionList *MEDIUM_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList)); 
  MEDIUM_QUIZ->head = NULL;
  question = fopen("../docs/quiz_related/questions/2_intermediate.txt", "r");
  answer = fopen("../docs/quiz_related/answers/2_intermediate.txt", "r");
  read_question(question, answer, &MEDIUM_QUIZ, MEDIUM);
  fclose(question);
  fclose(answer);

  QuestionList *HARD_QUIZ = (QuestionList *)calloc(1, sizeof(QuestionList));
  HARD_QUIZ->head = NULL;
  question = fopen("../docs/quiz_related/questions/3_advanced.txt", "r");
  answer = fopen("../docs/quiz_related/answers/3_advanced.txt", "r");
  read_question(question, answer, &HARD_QUIZ, HARD);
  fclose(question);
  fclose(answer);

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
      insert_at_end_ALL(&ALL, EASY_QUIZ, randomize());
    else if (i < 6)
      insert_at_end_ALL(&ALL, MEDIUM_QUIZ, randomize());
    else
      insert_at_end_ALL(&ALL, HARD_QUIZ, randomize());
  }

  show_questions(students[student_index], ALL, &ANSWER_STACK);
  show_final_result(&ANSWER_STACK);

  free(EASY_QUIZ);
  free(MEDIUM_QUIZ);
  free(HARD_QUIZ);
  free(ALL);
  free(ANSWER_STACK);
}

void show_final_result(AnswerNode **top_ref)
{
  const int score = calculate_score(top_ref);
  if (score >= PASSING_SCORE)
    show_pass_result(score);
  else
    show_fail_result(score);
  print_pause();
}

int calculate_score(AnswerNode **top_ref)
{
  int sum = 0;
  AnswerNode *ans;
  while ((ans = pop_answer(top_ref)) != NULL)
  {
    sum += ans->score_achieved;
    printf("%d\n", sum);
    free(ans);  // Free the popped node
  }
  return sum;
}

void show_pass_result(const int final_score)
{
  system("cls");
  printf("\n\n\n\n\n\n\n\n");
  printf("\t\t\t%5s __       ______   ______   .__   __.   _______ .______          ___   .___________.    _______.    __\n", " ");                                                                                       
  printf("\t\t\t%5s|  |     /      | /  __  \\  |  \\ |  |  /  _____||   _  \\        /   \\  |           |   /       |   |  |\n", " ");
  printf("\t\t\t%5s|  |    |  ,----'|  |  |  | |   \\|  | |  |  __  |  |_)  |      /  ^  \\ `---|  |----`  |   (----`   |  |\n", " ");
  printf("\t\t\t%5s|  |    |  |     |  |  |  | |  . `  | |  | |_ | |      /      /  /_\\  \\    |  |        \\   \\       |  |\n", " ");
  printf("\t\t\t%5s|__|    |  `----.|  `--'  | |  |\\   | |  |__| | |  |\\  \\----./  _____  \\   |  |    .----)   |      |__|\n", " ");
  printf("\t\t\t%5s(__)     \\______| \\______/  |__| \\__|  \\______| | _| `._____/__/     \\__\\  |__|    |_______/       (__)\n", " ");
  printf("\n");                                                                                                                                                                                             
  printf("\t\t\t____    ____  ______    __    __     .______      ___           _______.     _______. _______  _______      ___\n");  
  printf("\t\t\t\\   \\  /   / /  __  \\  |  |  |  |    |   _  \\    /   \\         /       |    /       ||   ____||       \\     \\  \\\n"); 
  printf("\t\t\t \\   \\/   / |  |  |  | |  |  |  |    |  |_)  |  /  ^  \\       |   (----`   |   (----`|  |__   |  .--.  |   (_)  |\n");
  printf("\t\t\t  \\_    _/  |  |  |  | |  |  |  |    |   ___/  /  /_\\  \\       \\   \\        \\   \\    |   __|  |  |  |  |     |  |\n");
  printf("\t\t\t    |  |    |  `--'  | |  `--'  |    |  |     /  _____  \\  .----)   |   .----)   |   |  |____ |  '--'  |    _|  |\n");
  printf("\t\t\t    |__|     \\______/   \\______/     | _|    /__/     \\__\\ |_______/    |_______/    |_______||_______/    (_)  |\n");
  printf("\t\t\t                                                                                                            /__/\n"); 
  printf("\n");
  printf("Your score is %d\n", final_score);
  print_pause();  
}

void show_fail_result(const int final_score)
{
  system("cls");
  printf("\n\n\n\n\n\n\n\n");
  printf("\t __    __  .__   __.  _______   ______   .______     .___________. __    __  .__   __.      ___   .___________. _______  __      ____    ____\n");  
  printf("\t|  |  |  | |  \\ |  | |   ____| /  __  \\  |   _  \\    |           ||  |  |  | |  \\ |  |     /   \\  |           ||   ____||  |     \\   \\  /   /\n"); 
  printf("\t|  |  |  | |   \\|  | |  |__   |  |  |  | |  |_)  |   `---|  |----`|  |  |  | |   \\|  |    /  ^  \\ `---|  |----`|  |__   |  |      \\   \\/   /\n");
  printf("\t|  |  |  | |  . `  | |   __|  |  |  |  | |      /        |  |     |  |  |  | |  . `  |   /  /_\\  \\    |  |     |   __|  |  |       \\_    _/\n");
  printf("\t|  `--'  | |  |\\   | |  |     |  `--'  | |  |\\  \\----.   |  |     |  `--'  | |  |\\   |  /  _____  \\   |  |     |  |____ |  `----.    |  |\n");
  printf("\t \\______/  |__| \\__| |__|      \\______/  | _| `._____|   |__|      \\______/  |__| \\__| /__/     \\__\\  |__|     |_______||_______|    |__|\n");                                                 
  printf("\n");                                                                                                                                                                                          
  printf("\t\t\t\t____    ____  ______    __    __      _______    ___       __   __       _______  _______     \n");
  printf("\t\t\t\t\\   \\  /   / /  __  \\  |  |  |  |    |   ____|  /   \\     |  | |  |     |   ____||       \\\n");
  printf("\t\t\t\t \\   \\/   / |  |  |  | |  |  |  |    |  |__    /  ^  \\    |  | |  |     |  |__   |  .--.  |\n"); 
  printf("\t\t\t\t  \\_    _/  |  |  |  | |  |  |  |    |   __|  /  /_\\  \\   |  | |  |     |   __|  |  |  |  |\n"); 
  printf("\t\t\t\t    |  |    |  `--'  | |  `--'  |    |  |    /  _____  \\  |  | |  `----.|  |____ |  '--'  |  \n"); 
  printf("\t\t\t\t    |__|     \\______/   \\______/     |__|   /__/     \\__\\ |__| |_______||_______||_______/\n"); 
  printf("\n");
  printf("Sorry, you need more %d points to pass the quiz. Please try again :D\n", PASSING_SCORE - final_score);
  print_pause();
}

void open_guide_book()
{
  FILE *file = fopen("../docs/guidebook/help.txt", "r");
  if (file == NULL) 
  {
    perror("Failed to open file");
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
    perror("Failed to allocate memory");
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

void open_report(Student *students)
{
  print_dashboard(students, NUM_STUDENTS);
  print_pause();
}

void show_questions(Student students, QuestionList *ques_all, AnswerNode **top_ref)
{
  Question* temp = ques_all->head;
  while (temp != NULL)
  {
    system("cls");
    char choice;
    int score_per_question = 0;
    printf("\n\n\n\n\n\n\n\n");
    printf("%s\n", temp->text);

    struct timeval start, end;
    long seconds, useconds;
    int elapsed;

    // Record the start time
    gettimeofday(&start, NULL);

    printf("\nYour answer: ");
    scanf("%c", &choice);
    fflush(stdin);

    // Record the end time
    gettimeofday(&end, NULL);

    // Calculate the time elapsed in microseconds
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + useconds / 1000000;

    printf("\n\n");

    if (elapsed > 15)
    {
      wrong_result_display(choice, temp->answer, "E");
      if (students.rate_score > 1)
        (students.rate_score)--;
    }
    else if (tolower(choice) != temp->answer)
    {
      wrong_result_display(choice, temp->answer, "Y");
      if (students.rate_score > 1)
        (students.rate_score)--;
    }
    else
    {
      correct_result_display();
      if (students.rate_score < 3)
        (students.rate_score)++;

      if (temp->difficulty == EASY)
        score_per_question += 2 * students.rate_score;
      else if (temp->difficulty == MEDIUM)
        score_per_question += 5 * students.rate_score;
      else if (temp->difficulty == HARD)
        score_per_question += 10 * students.rate_score;
    }
    push_answer(top_ref, temp->number, choice, score_per_question);

    if (temp->next == NULL)
      q_rest_timer(true);
    else
      q_rest_timer(false);

    temp = temp->next;
  }
}

void correct_result_display()
{
  printf("\t\t\t\t\t\t\t____    ____  _______     _______.    ___\n");
  printf("\t\t\t\t\t\t\t\\   \\  /   / |   ____|   /       |    \\  \\\n"); 
  printf("\t\t\t\t\t\t\t \\   \\/   /  |  |__     |   (----`   (_)  |\n");
  printf("\t\t\t\t\t\t\t  \\_    _/   |   __|     \\   \\         |  |\n");
  printf("\t\t\t\t\t\t\t    |  |     |  |____.----)   |       _|  |\n");
  printf("\t\t\t\t\t\t\t    |__|     |_______|_______/       (_)  |\n");
  printf("\t\t\t\t\t\t\t                                      /__/\n"); 
  printf("\n\t\t\t\t\t\t\t\tYOUR ANSWER IS CORRECT!!!\n");
}

void wrong_result_display(char student_ans, char correct_ans, char* reason)
{
  printf("\t\t\t\t\t\t\t%5s.__   __.   ______          ___  ___\n", " ");
  printf("\t\t\t\t\t\t\t%5s|  \\ |  |  /  __  \\      _ /  / /  /\n", " ");
  printf("\t\t\t\t\t\t\t%5s|   \\|  | |  |  |  |    (_)  | |  |\n", " "); 
  printf("\t\t\t\t\t\t\t%5s|  . `  | |  |  |  |      |  | |  |\n", " "); 
  printf("\t\t\t\t\t\t\t%5s|  |\\   | |  `--'  |     _|  | |  |\n", " "); 
  printf("\t\t\t\t\t\t\t%5s|__| \\__|  \\______/     (_)  | |  |\n", " "); 
  printf("\t\t\t\t\t\t\t%5s                           \\__\\ \\__\\\n", " ");
  if (reason[0] == 'E')
    printf("\n\t\t\t\t\t\t\t\tExceeding Time Limit, Sorry....\n");
  else
    printf("\n\t\t\t\t\t\t\t\t%5sCORRECT ANSWER IS %c\n\t\t\t\t\t\t\t\t%5sBUT YOUR ANSWER IS %c\n\n", " ", toupper(correct_ans), " ", toupper(student_ans));
}

AnswerNode *create_answer_node(int q_index, char student_ans, int score_achieved)
{
  AnswerNode *new_node = (AnswerNode *)calloc(1, sizeof(AnswerNode));
  new_node->question_index = q_index;
  new_node->student_answer = student_ans;
  new_node->score_achieved = score_achieved;
  new_node->next = NULL;
  return new_node;
}

void push_answer(AnswerNode **top_ref, int q_index, char student_ans, int score_achieved)
{
  AnswerNode* new_node = create_answer_node(q_index, student_ans, score_achieved);
  new_node->next = *top_ref;
  *top_ref = new_node;
}

AnswerNode *pop_answer(AnswerNode **top_ref)
{
  if (*top_ref == NULL)
    return NULL; // Stack is empty

  AnswerNode *temp = *top_ref;
  *top_ref = (*top_ref)->next;
  temp->next = NULL;
  return temp;
}

void read_question(FILE *question, FILE *answer, QuestionList **q_list, Level q_diff)
{
  char line[MAX_LINE_LENGTH], full_text[MAX_QUESTIONS];
  int number = 1, count = 0;

  while (fgets(line, sizeof(line), question)) 
  {
    // Remove trailing newline character
    line[strcspn(line, "\n")] = '\0';

    // Check if the line is a question
    if (line[0] >= '0' && line[0] <= '9') 
    {
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
      insert_at_end(q_list, full_text, q_diff, number, read_answer(answer, number));
      count = 0;
      full_text[0] = '\0';
      number++;
    }
  }
}

Question *create_question_node(char *q_text, Level q_diff, int number, char answer)
{
  Question *new_node = (Question *)calloc(1, sizeof(Question));
  new_node->number = number;
  strcpy(new_node->text, q_text);
  new_node->difficulty = q_diff;
  new_node->answer = answer;
  new_node->next = NULL;
  return new_node;
}

void insert_at_end(QuestionList **q_list, char *q_text, Level q_diff, int number, char answer)
{
  Question *new_node = create_question_node(q_text, q_diff, number, answer);
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

void insert_at_end_ALL(QuestionList **q_all, QuestionList *q_src, int q_num_from_src)
{
  // Ensure q_num_from_src is within the valid range
  if (q_num_from_src < 0 || q_num_from_src >= 10) 
  {
    printf("Invalid position specified.\n");
    return;
  }

  // Find the node at the specified position in the source list
  Question* temp_src = q_src->head;
  Question* prev_src = NULL;

  for (int i = 0; i < q_num_from_src && temp_src != NULL; i++) 
  {
    prev_src = temp_src;
    temp_src = temp_src->next;
  }

  // If the specified node is not found
  if (temp_src == NULL) 
  {
    printf("Node at the specified position not found.\n");
    return;
  }

  // Detach the node from the source list
  if (prev_src != NULL)
    prev_src->next = temp_src->next;
  else 
    q_src->head = temp_src->next;

  temp_src->next = NULL; // Ensure the detached node's next is set to NULL

  // Add the node to the end of the destination list
  if ((*q_all)->head == NULL) 
    (*q_all)->head = temp_src;
  else 
  {
    Question* temp_all = (*q_all)->head;
    while (temp_all->next != NULL) 
        temp_all = temp_all->next;
    temp_all->next = temp_src;
  }
}

char read_answer(FILE *file, int number) 
{
  char line[MAX_LINE_LENGTH], ret;
  int number_scanned;

  while (fgets(line, sizeof(line), file)) 
  {
    sscanf(line, "%d", &number_scanned);
    if (number_scanned == number)
      break;
  }

  for (int i = 0; line[i]; i++)
  {
    if (isalpha(line[i]))
      ret = line[i];
  }

  return ret;
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