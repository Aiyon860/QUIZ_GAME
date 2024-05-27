#include <stdio.h>
#include <windows.h>
#include "print_collections.h"

void print_header() 
{
  printf("\t\t\t\t____    __    ____  _______  __        ______   ______   .___  ___.  _______  __   __   __\n");  
  printf("\t\t\t\t\\   \\  /  \\  /   / |   ____||  |      /      | /  __  \\  |   \\/   | |   ____||  | |  | |  |\n"); 
  printf("\t\t\t\t \\   \\/    \\/   /  |  |__   |  |     |  ,----'|  |  |  | |  \\  /  | |  |__   |  | |  | |  |\n");
  printf("\t\t\t\t  \\            /   |   __|  |  |     |  |     |  |  |  | |  |\\/|  | |   __|  |  | |  | |  |\n"); 
  printf("\t\t\t\t   \\    /\\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____ |__| |__| |__|\n"); 
  printf("\t\t\t\t    \\__/  \\__/     |_______||_______| \\______| \\______/  |__|  |__| |_______|(__) (__) (__)\n");
  printf("\n\nSelamat Datang Di Kuis Syntax Bahasa C!\n");
  printf("[A] Mulai Kuis\n");
  printf("[B] Buka Buku Panduan (Harap melihat ini dulu sebelum memulai kuis)\n");
  printf("[C] Melihat Hasil Kuis\n");
  printf("[Q] Keluar\n");
  printf("Masukkan Pilihan: ");
}

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