#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "text.h"

void performChanges(char *fileName) {

  FILE *fp;
  int c;

  if (!(fp = fopen(fileName, "rt"))) {
    perror(fileName);
    exit(1);
  }
  while ((c = fgetc(fp)) != EOF) {
    
    printf("%c", c);
  }

  fclose(fp);
}