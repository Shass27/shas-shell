#include <stdio.h>
#include "functions.h"
#include <string.h>
#include "unistd.h"
#include "command.h"

int checkbuiltin(char *cmd) {
    char *builtincmds[] = {"cd", "help", "exit", "history"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(cmd, builtincmds[i]) == 0) return 1;
    }
    return 0;
}

void helpcmd() {
    printf("Apart from the system programs here are the following commands that have been built in the project:\n");
    printf("cd — change the current working directory\n");
    printf("Usage: cd <directory>\n");
    printf("\n");
    printf("history - show the list of commands passed so far\n");
    printf("Usage: history\n");
    printf("\n");
    printf("help — display information about built-in commands\n");
    printf("Usage: help\n");
    printf("\n");
    printf("exit — exit the shell\n");
    printf("Usage: exit\n");
    printf("\n");
}

void cdcmd(command command) {
    if (command.args[1] == NULL) chdir(getenv("HOME"));
    else {
        if (chdir(command.args[1]) == -1) {
            printf("cd: cannot access %s\n", command.args[1]);
        }
    }
}

void historycmd(char **history, int ncmd) {
    for (int i = 0; i < ncmd - 1; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}