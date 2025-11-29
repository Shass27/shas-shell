#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    char* line = NULL;
    size_t len = 0;
    ssize_t lread;

    while (1) {
        printf("shas-shell> ");
        fflush(stdout);

        lread = getline(&line, &len, stdin);

        if (lread == -1) {
            printf("\n");
            break;
        }

        if (line[lread - 1] == '\n') line[lread - 1] = '\0';

        if (lread==1) continue;

        if (!(strcmp(line, "exit"))) break;

        //test tokeniser
        char** tokens = tokenise(line);
        for (int i=0; tokens[i]!=NULL; i++) {
            printf("%s--", tokens[i]);
        }
        printf("\n");
    }
    free(line);
}