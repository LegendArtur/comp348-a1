#include "traversal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *myarg = NULL;

int main(int argc, char *argv[]) {

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
    printf("current working directory is: %s\n", cwd);
    listFilesRecursively(cwd);
  }


  return 0;
}
