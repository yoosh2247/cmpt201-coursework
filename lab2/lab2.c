#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *file = NULL;
  char *test;
  size_t size = 0;
  ssize_t len;
  int status;

  printf("Enter programs to run.");
  len = getline(&file, &size, stdin);

  // pretty sure I need a different pointer for second arg
  execlp(file, file);
  pid_t pid = fork();
  waitpid(pid, &status,
          WUNTRACED
#ifdef WCONTINUED
              | WCONTINUED
#endif
  );

  free(file);
  return 0;
}
