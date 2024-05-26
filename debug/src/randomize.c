#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

unsigned randomize()
{
  srand(time(NULL));
  unsigned r = rand() % 10;
  return r;
}

int main()
{
  for (int i = 0; i < 10; i++)
  {
    printf("%u\n", randomize());
    Sleep(1000);
  }
  return 0;
}