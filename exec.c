#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"
#include "command.h"

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t lread;

    char **history = NULL;
    int ncmds = 0;

    while (1) {
        char *dir = malloc(1024 * sizeof(char));
        getcwd(dir, 1024);
        int ns = -1;
        int len = strlen(dir);
        dir = realloc(dir, len + 1);
        //remove all the trailing slashes
        while (len > 1 && dir[len - 1] == '/')
            len--;
        for (int i = 0; i < len; i++) {
            if (dir[i] == '/') ns = i;
        }
        char *ldir = malloc(1024 * sizeof(char));
        for (int i = ns + 1; i < len; i++) {
            ldir[i - ns - 1] = dir[i];
        }
        ldir = realloc(ldir, strlen(ldir) + 1);
        printf("\033[1;32mshas-shell\033[0m:\033[1;34m%s\033[0m> ", ldir);
        free(ldir);
        free(dir);

        fflush(stdout);

        lread = getline(&line, &len, stdin);

        if (lread == -1) {
            printf("\n");
            break;
        }

        if (line[lread - 1] == '\n') line[lread - 1] = '\0';

        if (lread == 1) continue;

        history = realloc(history, (ncmds + 1) * sizeof(char *));
        history[ncmds] = malloc(sizeof(char) * (lread + 1));
        strcpy(history[ncmds++], line);

        char **tokens = tokenise(line);

        if (tokens[0] == NULL) continue;
        if (!(strcmp(line, "exit"))) break;

        for (int i = 1; tokens[i] != NULL; i++) {
            if (tokens[i][0] == '$' && tokens[i][1] != '\0') {
                int sw = strlen(tokens[i]);
                char *rt = malloc(sw * sizeof(char));
                for (int j = 0; j < sw - 1; j++) {
                    rt[j] = tokens[i][j + 1];
                }
                rt[sw - 1] = '\0';
                char *tenv = getenv(rt);
                if (tenv == NULL) tenv = "";
                int ntenv = strlen(tenv);
                tokens[i] = realloc(tokens[i], ntenv + 1);
                for (int j = 0; j < ntenv; j++) {
                    tokens[i][j] = tenv[j];
                }
                tokens[i][ntenv] = '\0';
                free(rt);
            }
        }

        command command = parse(tokens);

        if (checkbuiltin(tokens[0])) {
            if (!strcmp(tokens[0], "help")) {
                helpcmd(tokens);
            } else if (!strcmp(tokens[0], "cd")) {
                cdcmd(command);
            } else if (!strcmp(tokens[0], "history")) {
                historycmd(history, ncmds);
            }
        } else {
            run_cmd(command.cmd, command.args);
        }

        int x;
        for (int i = 0; tokens[i] != NULL; i++) {
            free(tokens[i]);
            x = i;
        }
        free(tokens[x + 1]);
        free(tokens);
        for (int i = 0; command.args[i] != NULL; i++) {
            free(command.args[i]);
            x = i;
        }
        free(command.args[x + 1]);
        free(command.args);
        free(command.cmd);
        command.args = NULL;
        command.cmd = NULL;
    }
    for (int i = 0; i < ncmds; i++) {
        free(history[i]);
    }
    free(history);
    free(line);
}