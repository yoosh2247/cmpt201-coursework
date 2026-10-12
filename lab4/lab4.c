#define _DEFAULT_SOURCE
#define BUF_SIZE 1024
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *e) {
  perror(e);
  exit(EXIT_FAILURE);
}

void *increase_heap_size() {
  size_t increase = 256 * sizeof(char);
  void *start = sbrk(increase);

  if (start == (void *)-1)
    handle_error("sbrk");

  return start;
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void initialize_block(struct header *block, int init) { memset(block, init, block->size); }

int main() {
  void *start_of_block = increase_heap_size();

  struct header *first_block = (struct header *)start_of_block;
  print_out("first block: %p\n", &first_block, sizeof(&first_block));
  start_of_block += 128;
  struct header *second_block = (struct header *)start_of_block;
  print_out("second block: %p\n", &second_block, sizeof(&second_block));

  first_block->size = 128;
  first_block->next = NULL;
  print_out("first block size: %d\n", &first_block->size, sizeof(&first_block->size));
  print_out("first block next: %p\n", &first_block->next, sizeof(&first_block->next));

  second_block->size = 128;
  second_block->next = first_block;
  print_out("second block size: %d\n", &second_block->size, sizeof(&second_block->size));
  print_out("second block next: %p\n", &second_block->next, sizeof(&second_block->next));

  //  print_out("first header: %p\n", first_block, sizeof(first_block));
  //  print_out("second header: %p\n", second_block, sizeof(second_block));

  initialize_block(first_block, 0);
  initialize_block(second_block, 1);

  //  print_out("first header: %p\n", first_block, sizeof(first_block));
  //  print_out("second header: %p\n", second_block, sizeof(second_block));

  // these loops give a seg fault at runtime
  // I think my initialize_block funtion is incorrect
  for (int i = 0; i < first_block->size; i++) {
    print_out("%d\n", &(*(first_block->next)), sizeof(&(*(first_block->next))));
  }

  for (int i = 0; i < second_block->size; i++) {
    print_out("%d\n", &(*(second_block->next)), sizeof(&(*(second_block->next))));
  }

  return 0;
}
