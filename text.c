#include <stdio.h>

void fix_text (FILE *f) {
    char x[1024];

    while (fscanf(f, " %1023s", x) == 1) {
        puts(x);
    }
}