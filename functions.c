#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//===========================================================================================================
void make_changes(char cCategory)
{
  int dChoice;
  if (cCategory == 'a')
  {
    system("clear");
    printf("Enter the corresponding number to mark an item as completed:\n");
    display_file("todo.txt");
    scanf("%d", &dChoice);

    FILE *fp, *fp_out, *fp_temp;
    char buffer[200];

    fp = fopen("todo.txt", "r");
    if (fp == NULL)
    {
      printf("Error opening file.\n");
      // return 1;
    }
    fp_out = fopen("completed.txt", "a");
    if (fp_out == NULL)
    {
      printf("Error opening file.\n");
      // return 1;
    }
    fp_temp = fopen("temp.txt", "w");
    if (fp_out == NULL)
    {
      printf("Error opening file.\n");
      // return 1;
    }

    int n = 1;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
      if (strcmp(buffer, "\n") == 0 || strcmp(buffer, "\r\n") == 0)
        continue; // skip the line
      if (n == dChoice)
        fputs(buffer, fp_out);
      else
        fputs(buffer, fp_temp);
      n++;
    }
    // printf("\n");

    fclose(fp);
    fclose(fp_out);
    fclose(fp_temp);

    fp = fopen("todo.txt", "w");
    fp_temp = fopen("temp.txt", "r");
    while (fgets(buffer, sizeof(buffer), fp_temp) != NULL)
    {
      fputs(buffer, fp);
    }
    fclose(fp);
    fclose(fp_temp);
    remove("temp.txt");

    //=================================================================
  }
  else if (cCategory == 'b')
  {
    system("clear");
    printf("Add your next task (type 'exit' to finish):\n");
    display_file("todo.txt");
    display_file_for_writing("todo.txt");
    system("clear");
    display_file("todo.txt");
  }



  else if (cCategory == 'q'){
    exit(0);
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