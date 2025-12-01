#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "command.h"

command parse(char** tokens) {
    int i=0;
    int na=0;
    command command;
    command.cmd = malloc(strlen(tokens[0])+1);
    strcpy(command.cmd,tokens[i]);
    command.args = NULL;
    while (tokens[i]!=NULL) {
        command.args = realloc(command.args, (na+2)*sizeof(char*));
        command.args[na] = malloc(strlen(tokens[i])+1);
        strcpy(command.args[na++], tokens[i++]);
    }
    command.args[na] = NULL;
    command.narg = na;
    return command;
}