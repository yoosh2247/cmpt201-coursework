#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *file = NULL;
  char *test = "ls";
  size_t size = 0;
  ssize_t len;
  int status;

  while (1) {
    printf("Enter programs to run. \n");
    len = getline(&file, &size, stdin);

    // pretty sure I need a different pointer for second arg
    execlp(file, test);
    pid_t pid = fork();
    waitpid(pid, &status,
            WUNTRACED
#ifdef WCONTINUED
                | WCONTINUED
#endif
    );
  }
  free(file);
  return 0;
}
