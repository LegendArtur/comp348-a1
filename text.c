#include "text.h"
#include "replace.h"
#include "report.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int numberOfChanges = 0;

//finds and capitalizes targeter word
static void addLine(char *line, FILE *tempFile) {

  // check each char
  for (int i = 0; i < strlen(line); i++) {
    // if same character as first word
    if (toupper(line[i]) == toupper(myarg[0])) {

      // check if its the same word
      for (int y = 0; myarg[y] != '\0'; y++) {

        // if it's not then stop
        if (toupper(line[i + y]) != toupper(myarg[y])) {
          break;
        }

        // if it is Capitalize the word and put cursor to following char
        if (myarg[y + 1] == '\0') {
          numberOfChanges++;

          for (int k = 0; k <= y; k++) {
            fputc(toupper(line[i + k]), tempFile);
          }

          i += y + 1;
        }
      }
    }

    // put each character
    if (i != strlen(line)) {
      fputc(line[i], tempFile);
    }
  }
}

//performs changes 
void performChanges(char *fileName) {
  FILE *file = fopen(fileName, "rt");
  FILE *tempFile = fopen("temp.txt", "w");

  char buffer[256];

  while ((fgets(buffer, sizeof(buffer), file)) != NULL) {
    addLine(buffer, tempFile);
  }

  rename("temp.txt", fileName);
  addChange(fileName, numberOfChanges);
  numberOfChanges = 0;
}
