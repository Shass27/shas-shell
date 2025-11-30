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

        //test parser
        char** tokens = tokenise(line);
        command command = parse(tokens);
        printf("Given Command: %s\n", command.cmd);
        int n = command.narg;
        printf("Number of arguments: %d\n", n);
        printf("Given arguments: ");
        for (int i = 0; i < n; i++) {
            printf("%s -- ", command.args[i]);
        }
        printf("\n");
    }
    free(line);
}