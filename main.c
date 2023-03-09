#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
  char cCategory;
  while (1)
  {
    system("clear");
    printf("Due:\n");
    display_file("todo.txt");
    printf("Completed:\n");
    display_file("completed.txt");
    printf("=========================================\n");
    printf("a) Mark item as completed -----> type 'a'\n");
    printf("b) Add new item ---------------> type 'b'\n");
    printf("c) Remove existing item -------> type 'c'\n");
    printf("q) Quit -----------------------> type 'q'\n");
    printf("=========================================\n");
    cCategory = 'x';
    do
    {
      printf("Enter your choice: ");
      scanf(" %c", &cCategory);
    } while (cCategory != 'a' && cCategory != 'b' && cCategory != 'c' && cCategory != 'q');

    make_changes(cCategory);
  }

  return 0;
}
