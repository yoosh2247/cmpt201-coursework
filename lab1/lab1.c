#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *line = NULL, *saveptr, *tokenptr;
  size_t size = 0;
  ssize_t len;

  printf("Please enter some text: ");
  len = getline(&line, &size, stdin);

  if (len == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  printf("Tokens:");
  tokenptr = strtok_r(line, " ", &saveptr);

  while (tokenptr != NULL) {
    printf("\n ");
    for (int i = 0; tokenptr[i] != '\0'; i++) {
      printf("%c", tokenptr[i]);
    }
    tokenptr = strtok_r(NULL, " ", &saveptr);
  }

  free(line);
  return 0;
}
