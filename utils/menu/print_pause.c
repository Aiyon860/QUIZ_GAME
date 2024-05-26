#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "print_collections.h"

bool print_pause()
{
  char choice;
  bool isLoop = true;

  // Confirmation dialog
  printf("\n\n\t\t\t\t\t\t\t%sTekan \"ENTER\" untuk kembali ke menu utama: ", "  ");
  scanf("%c", &choice);
  fflush(stdin);

  switch (choice) 
  {
    case '\n':
      isLoop = false;
      break;
    default:
      fprintf(stderr, "\n\t\t\t\t\t\tInput yang Anda masukkan tidak dimengerti, Silahkan coba kembali");
      Sleep(3000);
  }
  
  return isLoop;
}