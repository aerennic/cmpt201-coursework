#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *buffer = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n> ");
    fflush(stdout);

    if (getline(&buffer, &len, stdin) == -1) { // invalid input
      break;
    }

    // strip newline
    buffer[strcspn(buffer, "\n")] = '\0';

    pid_t pid = fork();
    if (pid == 0) {
      execl(buffer, buffer, NULL);

      printf("Exec failure\n");
      exit(1);
    } else if (pid > 0) {
      waitpid(pid, NULL, 0);
    }
  }

  free(buffer);
  return 0;
}
