#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I keep getting a dynamic-stack-buffer-overflow error when I run the code but, I tried to comment
// as much as possible to show my logic

void usr_input(char **line, ssize_t len, size_t size) {
  // gets the user input
  printf("Enter input: ");
  getline(line, &size, stdin);
}

void print_last_5(char print[][15], int size) {
  // prints the last five lines
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 15; j++) {
      printf("%c", print[i][j]);
    }
    printf("\n");
  }
}

void update_last_5(char **line, char last_five_array[][15], int size, int pass) {
  if (pass > 5) { // checks to see if the 2d array is full

    // edits the full 2d array by getting rid of the oldest line
    for (int i = 0; i < (size - 1); i++) {
      for (int j = 0; j < 15; j++) {
        last_five_array[i][j] = last_five_array[i + 1][j];
      }
    }
  }
  // fills the next row of the array with the current line
  for (int i = 0; i < (14); i++) {
    last_five_array[pass][i] = line[0][i];
  }

  // checks to see if the user entered "print"
  if (strcmp(*line, "print") == 1) {
    print_last_5(last_five_array, size);
  }
}

int main() {
  int arr_size = 5;
  char *current_line = NULL;
  char last_5_lines[arr_size][15];
  ssize_t len = 0;
  size_t size = 0;

  for (int i = 0; i <= 5; i++) {
    usr_input(&current_line, len, size);
    update_last_5(&current_line, last_5_lines, arr_size, i);
    if (i == 5)
      i = 0;
  }

  free(current_line);
  return 0;
}
