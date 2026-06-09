#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256
#define BLOCK_SIZE 128
#define HEAP_SIZE 256

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *msg) {
  write(STDERR_FILENO, msg, strlen(msg));
  write(STDERR_FILENO, "\n", 1);
  exit(1);
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

int main() {
  void *heap_start = sbrk(HEAP_SIZE);
  if (heap_start == (void *)-1) {
    handle_error("sbrk");
  }

  struct header *first_block = (struct header *)heap_start;
  struct header *second_block = (struct header *)((void *)heap_start + BLOCK_SIZE);

  first_block->size = BLOCK_SIZE;
  first_block->next = NULL;

  second_block->size = BLOCK_SIZE;
  second_block->next = first_block;

  void *first_data = (void *)first_block + sizeof(struct header);
  size_t data_size = BLOCK_SIZE - sizeof(struct header);
  memset(first_data, 0, data_size);

  void *second_data = (void *)second_block + sizeof(struct header);
  memset(second_data, 1, data_size);

  print_out("first block:       %p\n", (void *)&first_block, sizeof(first_block));
  print_out("second block:      %p\n", (void *)&second_block, sizeof(second_block));

  print_out("first block size:  %lu\n", &first_block->size, sizeof(uint64_t));
  print_out("first blcok next:  %p\n", &first_block->next, sizeof(first_block->next));
  print_out("second block size: %lu\n", &second_block->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &second_block->next, sizeof(second_block->next));

  uint8_t *p = (uint8_t *)first_data;
  for (size_t i = 0; i < data_size; i++) {
    uint64_t val = p[i];
    print_out("%lu\n", &val, sizeof(uint64_t));
  }

  p = (uint8_t *)second_data;
  for (size_t i = 0; i < data_size; i++) {
    uint64_t val = p[i];
    print_out("%lu\n", &val, sizeof(uint64_t));
  }

  return 0;
}
