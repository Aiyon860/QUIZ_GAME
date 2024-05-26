// Preprocessor
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "../utils/menu/print_collections.h"

int main()
{
  FILE *file = fopen("../docs/guidebook/help.txt", "r");
  if (!file) 
  {
    perror("Failed to open file");
    return EXIT_FAILURE;
  }

  // Seek to the end of the file to get the size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET); // Go back to the beginning of the file

  // Allocate memory to hold the file content plus a null terminator
  char *buffer = (char*)malloc(fileSize + 1);
  if (!buffer) 
  {
    perror("Failed to allocate memory");
    fclose(file);
    return EXIT_FAILURE;
  }

  // Read the file content into the buffer
  size_t bytesRead = fread(buffer, 1, fileSize, file);

  // Null-terminate the buffer
  buffer[bytesRead] = '\0';

  // Loop the menu
  bool isLoop = true;
  char choice;
  while (isLoop) 
  {
    // Print the buffer
    printf("%s\n", buffer);
    isLoop = print_pause();
  }

  // Free the allocated memory and close the file
  free(buffer);
  fclose(file);
  return EXIT_SUCCESS;
}