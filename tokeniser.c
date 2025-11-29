#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** tokenise(char* line) {
    int n = strlen(line);
    char** tokens = NULL;
    int i = 0;
    int nw=0;
    while (i < n) {
        if (line[i]==' ') {
            i++;
            continue;
        }
        nw++;
        tokens = realloc(tokens, nw * sizeof(char*));
        int j=0;
        tokens[nw-1] = NULL;
        while (i<n && line[i]!=' ') {
            j++;
            tokens[nw-1] = realloc(tokens[nw-1], j+1);
            tokens[nw-1][j-1]=line[i++];
        }
        tokens[nw-1][j]='\0';
    }
    tokens = realloc(tokens, (nw+1)*sizeof(char*));
    tokens[nw] = NULL;
    return tokens;
}