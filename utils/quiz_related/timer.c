#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/time.h>
#include "timer.h"

int randomize()
{
  srand(time(NULL));
  int r = rand() % 6;
  return r;
}

void q_rest_timer(bool is_last) 
{ 
  if (is_last)
    printf("\t\t\t\t\t\t\t%3sTunggu 10 detik untuk menunggu pengumuman....\n", " ");
  else
    printf("\t\t\t\t\t\t\t%3sTunggu 5 detik untuk melanjutkan kuis....\n", " ");

  Sleep(5000);
}