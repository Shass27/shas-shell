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
        char *dir = malloc(1024 * sizeof(char));
        getcwd(dir, 1024);
        int ns = -1;
        int len = strlen(dir);
        dir = realloc(dir, len + 1);
        //remove all the trailing slashes
        while (len > 1 && dir[len-1] == '/')
            len--;
        for (int i = 0; i < len; i++) {
            if (dir[i] == '/') continue;
            if (dir[i] == '/') ns = i;
        }
        char *ldir = malloc(1024 * sizeof(char));
        for (int i = ns + 1; i < len; i++) {
            ldir[i - ns - 1] = dir[i];
        }
        ldir = realloc(ldir, strlen(ldir) + 1);
        printf("shas-shell:%s> ", ldir);
        free(ldir);
        free(dir);

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