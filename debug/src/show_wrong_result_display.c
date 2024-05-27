#include <stdio.h>

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
    printf("\n\t\t\t\t\t\t\t\tExceeding Time Limit, Sorry....\n\n");
  else
    printf("\n\t\t\t\t\t\t\t\t%5sCORRECT ANSWER IS %c\n\t\t\t\t\t\t\t\t%5sBUT YOUR ANSWER IS %c\n\n", " ", correct_ans, " ", student_ans);
}

int main(int argc, char const *argv[])
{
  wrong_result_display('A', 'B', "E");
  wrong_result_display('A', 'B', "C");
  return 0;
}
