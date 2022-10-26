#include "text.h"
#include "report.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void listFilesRecursively(char *path);

int ends_with_txt(const char *str) {
  char *dot = strrchr(str, '.');

  if (NULL == dot)
    return 0;
  return strcmp(dot, ".txt") == 0;
}


//Opens files and sub-directories recursively considering path as base path.
void listFilesRecursively(char *basePath) {
  char path[1000];
  struct dirent *dp;
  DIR *dir = opendir(basePath);

  // Unable to open directory stream
  if (!dir) {
    return;
  }
  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {

      // Construct new path from our base path
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      if (ends_with_txt(dp->d_name)) {
        performChanges(path);
      } else {
        listFilesRecursively(path);
      }
    }
  }

  closedir(dir);
}