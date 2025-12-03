#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"
#include "command.h"

int main() {
    char* line = NULL;
    size_t len = 0;
    ssize_t lread;

    while (1) {
        printf("shas-shell> %s % ", getcwd(NULL, 0));
        fflush(stdout);

        lread = getline(&line, &len, stdin);

        if (lread == -1) {
            printf("\n");
            break;
        }

        if (line[lread - 1] == '\n') line[lread - 1] = '\0';

        if (lread==1) continue;
        char** tokens = tokenise(line);

        if (tokens[0]==NULL) continue;
        if (!(strcmp(line, "exit"))) break;

        command command = parse(tokens);

        if (checkbuiltin(tokens[0])) {
            if (!strcmp(tokens[0], "help")) {
                helpcmd(tokens);
            }
            else if (!strcmp(tokens[0], "cd")) {
                cdcmd(command);
            }
        }
        else {
            run_cmd(command.cmd, command.args);
        }

        for (int i=0; tokens[i]!=NULL; i++) {
            free(tokens[i]);
        }
        free(tokens);
        for (int i=0; command.args[i]!=NULL; i++) {
            free(command.args[i]);
        }
        free(command.args);
        free(command.cmd);
        command.args = NULL;
        command.cmd = NULL;
    }
    free(line);
}