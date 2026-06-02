#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 5

// Global Variables
int counter = 0;
char *input_history[MAX_LEN];

void add_to_history(char *input);
void remove_oldest_record();
void print();
char *get_input();

int main() {
  while (1) {
    char *input = get_input();
    add_to_history(input);
    if (strcmp(input, "print") == 0) {
      print();
    }
  }

  // Free the memory of the input history
  while (counter > 0) {
    remove_oldest_record();
  }

  return 0;
}

char *get_input() {
  char *buffer = NULL;
  size_t bufsize = 0;
  printf("Enter input: ");
  ssize_t len = getline(&buffer, &bufsize, stdin);
  if (len == -1) {
    printf("Invalid input. Exiting.\n");
    exit(1);
  }

  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
  }
  return buffer;
}

void add_to_history(char *input) {
  if (counter >= MAX_LEN) {
    remove_oldest_record();
  }
  input_history[counter] = input;
  counter++;
}

void remove_oldest_record() {
  if (counter > 0) {
    free(input_history[0]);
    for (int i = 1; i < counter; i++) {
      input_history[i - 1] = input_history[i];
    }
    counter--;
  }
}

void print() {
  for (int i = 0; i < counter; i++) {
    printf("%s\n", input_history[i]);
  }
}
