#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "functions.h"
#include <unistd.h>
#include <sys/wait.h>

void run_cmd(char *cmd, char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(cmd, args);
        printf("Err exec cmd or cmd not found\n");
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        printf("Err exec cmd or cmd not found\n");
    }
}