#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// one Change contains the file path, number of changes in that file
typedef struct Changes {
  int number;
  char *fileName;
} Change;

Change *changes = NULL;
int currentChangesCount = 0;

// compare function comaring the number of updates in one change
int compare(const void *a, const void *b) {
  int l = ((Change *)a)->number;
  int r = ((Change *)b)->number;
  return (l - r);
}

// report.txt generator
void initializeReport(char *fileName, char *targetString) {

  // create the file
  FILE *reportFile = fopen("report.txt", "w");
  fprintf(reportFile,
          "Target string: %s\nSearch begins in current folder: "
          "%s\n\n------Report------\n"
          "Updates\t\tFile Name\n",
          targetString, fileName);

  // qsort the array
  qsort(changes, currentChangesCount, (sizeof(*changes)), compare);
  for (int i = currentChangesCount - 1; i >= 0; i--) {
    fprintf(reportFile, "%d\t\t\t%s\n", changes[i].number, changes[i].fileName);
  }

  // free memory
  free(changes);
  changes = NULL;
  fclose(reportFile);
}

// add a change to the list with the name and number of updates
void addChange(char *fileName, int numberOfChanges) {
  Change *temp = realloc(changes, (currentChangesCount + 1) * sizeof(*changes));
  if (temp != NULL) {
    changes = temp;
  } else {
    return;
  }
  Change *c = malloc(sizeof(Change));

  c->number = numberOfChanges;

  c->fileName = malloc(strlen(fileName) + 1);
  if (NULL == c->fileName) {
    perror("malloc for fileName failed");
    exit(EXIT_FAILURE);
  }
  strcpy(c->fileName, fileName);

  changes[currentChangesCount] = *c;
  currentChangesCount++;
}