#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Changes {
  int number;
  char fileName[256];
} Change;

Change *changes = NULL;
int currentChangesCount = 0;

int compare(const void *a, const void *b) {
  int l = ((Change *)a)->number;
  int r = ((Change *)b)->number;
  return (l - r);
}

void initializeReport(char *fileName, char *targetString) {

  printf("%s", targetString);
  FILE *reportFile = fopen("report.txt", "w");
  fprintf(reportFile,
          "Target string: %s\nSearch begins in current folder: %s\n\n------Report------\n",
          targetString, fileName);

//   qsort(changes, sizeof(*changes)/sizeof(changes[0]),sizeof(int) + sizeof(char[256]), compare);

  fclose(reportFile);
}

// void addChange(char *fileName, int *numberOfChanges) {
//   changes = realloc(changes, currentChangesCount + 1 * sizeof(*changes));
//   Change *c = malloc(sizeof(Change));
//   c->number = *numberOfChanges;
//   changes[currentChangesCount] = *c;
//   currentChangesCount++;
// }