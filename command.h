#ifndef SHAS_SHELL_COMMAND_H
#define SHAS_SHELL_COMMAND_H

typedef struct {
    char *cmd;
    char **args;
    int narg;
} command;
#endif //SHAS_SHELL_COMMAND_H