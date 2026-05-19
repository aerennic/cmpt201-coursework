#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char buffer[32];
  char *b = buffer;
  size_t len = 0;
  size_t temp;

  printf("Please enter some text: ");
  temp = getline(&b, &len, stdin);

  while (temp != -1) {
    printf("Tokens:\n");

    char *saveptr = NULL;
    char *ret = strtok_r(b, " ", &saveptr);
    printf("%s\n", ret);
    while ((ret = strtok_r(NULL, " ", &saveptr))) {
      printf("%s\n", ret);
    }

    printf("PLease enter some text: ");
    temp = getline(&b, &len, stdin);
  }

  if (temp == -1) {
    perror("getline failed");
    free(b);
    exit(EXIT_FAILURE);
  }

  free(b);
  return 0;
}
