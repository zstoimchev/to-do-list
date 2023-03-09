#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
  char cCategory, *options[] = {"Options:\n",
                                "=========================================\n",
                                "a) Mark item as completed -----> type 'a'\n",
                                "b) Add new item ---------------> type 'b'\n",
                                "c) Remove existing item -------> type 'c'\n",
                                "q) Quit -----------------------> type 'q'\n",
                                "=========================================\n"};
  while (1)
  {
    system("clear");
    printf("Due:\n");
    display_file("todo.txt");
    printf("Completed:\n");
    display_file("completed.txt");
    for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++)
      printf("%s", options[i]);
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
