#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "timer.h"

int randomize()
{
  srand(time(NULL));
  int r = rand() % 10;
  return r;
}

void q_timer() 
{ 
  Sleep(15000); 
}