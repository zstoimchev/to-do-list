#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <unistd.h>

//===========================================================================================================
void check_file()
{
  FILE *todo_file = fopen("todo.txt", "r");
  if (todo_file == NULL)
  {
    printf("todo.txt does not exist. Creating file...\n");
    todo_file = fopen("todo.txt", "w");
    if (todo_file == NULL)
    {
      printf("Error creating todo.txt\n");
      exit(1);
    }
    fclose(todo_file);
  }

  FILE *completed_file = fopen("completed.txt", "r");
  if (completed_file == NULL)
  {
    printf("completed.txt does not exist. Creating file...\n");
    completed_file = fopen("completed.txt", "w");
    if (completed_file == NULL)
    {
      printf("Error creating completed.txt\n");
      exit(1);
    }
    fclose(completed_file);
  }
}
//===========================================================================================================
void clear_screen()
{
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#endif
}
//===========================================================================================================
void make_changes(char cCategory[3])
{
  int dChoice;
  if (strcmp(cCategory, "a") == 0)
  {
    clear_screen();
    printf("Enter the corresponding number to mark an item as completed:\n");
    display_file("todo.txt");
    scanf("%d", &dChoice);
    complete_task(dChoice);
  }
  else if (strcmp(cCategory, "b") == 0)
  {
    clear_screen();
    printf("Add your next task (type 'exit' to finish):\n");
    display_file("todo.txt");
    append_file("todo.txt");
  }
  else if (strcmp(cCategory, "c") == 0)
  {
    clear_screen();
    printf("Enter the corresponding number to remove an item:\n");
    display_file("todo.txt");
    scanf("%d", &dChoice);
    delete_item(dChoice);
  }
  else if (strcmp(cCategory, "d") == 0)
  {
    clear_screen();
    printf("Enter the corresponding number to remove an item:\n");
    display_file("completed.txt");
    scanf("%d", &dChoice);
    delete_completed(dChoice);
  }
  else if (strcmp(cCategory, "q") == 0)
  {
    exit(0);
  }
}
//===========================================================================================================
void delete_completed(int dChoice)
{
  FILE *fp, *fp_temp;
  char buffer[200];
  fp = fopen("completed.txt", "r");
  if (fp == NULL)
    printf("Error opening file.\n");
  fp_temp = fopen("temp.txt", "w");
  if (fp_temp == NULL)
    printf("Error opening file.\n");

  int n = 1;
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    if (n == dChoice)
    {
      n++;
      continue;
    }
    else
    {
      fputs(buffer, fp_temp);
      n++;
    }
  }
  fclose(fp);
  fclose(fp_temp);

  fp = fopen("completed.txt", "w");
  fp_temp = fopen("temp.txt", "r");
  while (fgets(buffer, sizeof(buffer), fp_temp) != NULL)
  {
    fputs(buffer, fp);
  }
  fclose(fp);
  fclose(fp_temp);
  remove("temp.txt");
}
//===========================================================================================================
void delete_item(int dChoice)
{
  FILE *fp, *fp_temp;
  char buffer[200];
  fp = fopen("todo.txt", "r");
  if (fp == NULL)
    printf("Error opening file.\n");
  fp_temp = fopen("temp.txt", "w");
  if (fp_temp == NULL)
    printf("Error opening file.\n");

  int n = 1;
  while (fgets(buffer, sizeof(buffer), fp) != NULL)
  {
    if (n == dChoice)
    {
      n++;
      continue;
    }
    else
      fputs(buffer, fp_temp);
    n++;
  }

  fclose(fp);
  fclose(fp_temp);

  fp = fopen("todo.txt", "w");
  fp_temp = fopen("temp.txt", "r");
  while (fgets(buffer, sizeof(buffer), fp_temp) != NULL)
    fputs(buffer, fp);
  fclose(fp);
  fclose(fp_temp);
  remove("temp.txt");
}
//===========================================================================================================
void complete_task(int dChoice)
{
  FILE *fp, *fp_out, *fp_temp;
  char buffer[200];

  fp = fopen("todo.txt", "r");
  if (fp == NULL)
    printf("Error opening file.\n");
  fp_out = fopen("completed.txt", "a");
  if (fp_out == NULL)
    printf("Error opening file.\n");
  fp_temp = fopen("temp.txt", "w");
  if (fp_out == NULL)
    printf("Error opening file.\n");

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
    fputs(buffer, fp);
  fclose(fp);
  fclose(fp_temp);
  remove("temp.txt");
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
void append_file(char sFileName[10])
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