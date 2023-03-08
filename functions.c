#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void display_file_for_writing(char sFileName[10])
{
  FILE *fp;
  const size_t BUFFER_SIZE = 101; // define the buffer size using size_t
  char buffer[BUFFER_SIZE];

  fp = fopen(sFileName, "a");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  while (1)
  {
    fgets(buffer, BUFFER_SIZE, stdin); // read a line of input from the user
    if (strcmp(buffer, "exit\n") == 0) // if user types 'exit', stop writing to file
      break;
    fputs(buffer, fp); // write the input to file
                       // fputc('\n', fp);
  }

  fclose(fp);
}
//===========================================================================================================
void make_changes(char cCategory)
{
  switch (cCategory)
  {
  case 'a':

    break;
  case 'b':
    system("clear");
    printf("Add your next task (type 'exit' to finish):\n");
    display_file("todo.txt");
    display_file_for_writing("todo.txt");
    system("clear");
    display_file("todo.txt");
    break;
  case 'c':
    display_file("third.txt");
    break;
  case 'q':
    exit(0);
    break;
  default:
    break;
  }
}
//===========================================================================================================
void display_file(char sFileName[10])
{
  FILE *fp;
  const size_t BUFFER_SIZE = 101; // define the buffer size using size_t
  char buffer[BUFFER_SIZE];

  fp = fopen(sFileName, "r");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    // return 1;
  }

  int n = 1;
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
  {
    if (strcmp(buffer, "\n") == 0 || strcmp(buffer, "\r\n") == 0)
      continue; // skip the line

    printf("\t%d. %s", n, buffer); // print the line to the console
    n++;
  }
  printf("\n");

  fclose(fp);
}
//===========================================================================================================