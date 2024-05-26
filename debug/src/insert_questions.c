/*
 * Objective:
 * -> Checking if the questions from .txt read successfully.
 */

// Preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_QUESTIONS 1000

typedef struct {
    char text[MAX_LINE_LENGTH * 6]; // Buffer to hold the entire question and options
} Question;

void parse_questions(FILE *file, Question questions[], int *num_questions) 
{
  char line[MAX_LINE_LENGTH];
  int question_index = -1;

  while (fgets(line, sizeof(line), file)) 
  {
    // Remove trailing newline character
    line[strcspn(line, "\n")] = '\0';

    // Check if the line is a question
    if (line[0] >= '0' && line[0] <= '9') 
    {
      question_index++;
      strcpy(questions[question_index].text, line);
      strcat(questions[question_index].text, "\n"); // Add newline for formatting
    } 
    else if (line[0] >= 'a' && line[0] <= 'd' && line[1] == ')') 
    {
      strcat(questions[question_index].text, line);
      strcat(questions[question_index].text, "\n"); // Add newline for formatting
    }
  }

  *num_questions = question_index + 1;
}

// Main Entry Point
int main()
{
  FILE *file = fopen("../docs/quiz_related/questions/1_beginner.txt", "r");
  if (!file) 
  {
    perror("Unable to open file");
    return EXIT_FAILURE;
  }

  Question questions[MAX_QUESTIONS];
  int num_questions = 0;

  parse_questions(file, questions, &num_questions);

  fclose(file);

  // Print the parsed questions, options, and answers
  for (int i = 0; i < num_questions; i++) 
  {
    printf("%s", questions[i].text);
    printf("\n");
  }

  return EXIT_SUCCESS;
}