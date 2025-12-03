#ifndef SHAS_SHELL_FUNCTIONS_H
#define SHAS_SHELL_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "command.h"

char** tokenise(char* line);
command parse (char** tokens);
void run_cmd(char* cmd, char** args);
int checkbuiltin(char *cmd);
void helpcmd();
void cdcmd(command command);
#endif