#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
  check_file(); // this needs more more and more work
  char cCategory[3] = "x", *options[] = {"Options:\n",
                                         "==========================================================\n",
                                         "a) Mark item as completed ----------------------> type 'a'\n",
                                         "b) Add new item --------------------------------> type 'b'\n",
                                         "c) Remove existing item from 'to-do/due' list --> type 'c'\n",
                                         "d) Remove existing item from 'completed' list --> type 'd'\n",
                                         "q) Quit ----------------------------------------> type 'q'\n",
                                         "==========================================================\n"};
  while (1)
  {

    do
    {
      clear_screen();
      printf("Due:\n");
      display_file("todo.txt");
      printf("----------------------------------------------------------\n");
      printf("Completed:\n");
      display_file("completed.txt");
      printf("\n");
      for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++)
        printf("%s", options[i]);
      printf("Enter your choice: ");
      scanf("%s", cCategory);
    } while (strcmp(cCategory, "a") != 0 && strcmp(cCategory, "b") != 0 && strcmp(cCategory, "c") != 0 && strcmp(cCategory, "d") != 0 && strcmp(cCategory, "q") != 0);
    make_changes(cCategory);
  }

  return 0;
}
