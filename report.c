#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//one Change contains the file path, number of changes in that file
typedef struct Changes {
  int number;
  char *fileName;
} Change;

Change *changes = NULL;
int currentChangesCount = 0;

int compare(const void *a, const void *b) {
  int l = ((Change *)a)->number;
  int r = ((Change *)b)->number;
  return (l - r);
}

void initializeReport(char *fileName, char *targetString) {

  FILE *reportFile = fopen("report.txt", "w");
  fprintf(reportFile,
          "Target string: %s\nSearch begins in current folder: "
          "%s\n\n------Report------\n"
          "Updates\t\tFile Name\n",
          targetString, fileName);

  // sort the array
  qsort(changes, sizeof(*changes) / sizeof(changes[0]),
        sizeof(int) + sizeof(char[256]), compare);
  for (int i = currentChangesCount-1; i >= 0; i--) {
    fprintf(reportFile, "%d\t\t\t%s\n", changes[i].number, changes[i].fileName);
  }

  free(changes);
  changes = NULL;
  fclose(reportFile);
}

void addChange(char *fileName, int numberOfChanges) {
  Change *temp = realloc(changes, (currentChangesCount + 1) * sizeof(*changes));
  if (temp != NULL)
    changes = temp;
  else
    exit(1);

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