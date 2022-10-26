#include "report.h"
#include "traversal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *myarg = NULL;

int main(int argc, char *argv[]) {

  // if report exists remove it
  if (access("report.txt", F_OK) == 0) {
    remove("report.txt");
  }

  if (argc != 2) {
    printf("Please enter : ./a WORD_TO_FIND\n");
    return -1;
  }

  myarg = argv[1];

  char cwd[256];

  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd() error");
    exit(1);
  }

  else {
    printf("Current working directory is: %s\n", cwd);
    listFilesRecursively(cwd);
  }

  initializeReport(cwd, myarg);
  return 0;
}
