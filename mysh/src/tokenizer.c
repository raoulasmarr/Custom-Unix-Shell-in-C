#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

char **tokenize(char *line,int *argc){
    char **result = calloc(MAX_ARGS+1, sizeof(char *));
    if(result == NULL)
        return NULL;
    const char *delimiter = " \n";
    char *savept = NULL;
    char *word = strtok_r(line, delimiter, &savept);
    int i=0;
    while(word != NULL && i<MAX_ARGS){
        result[i] = strdup(word);
        word = strtok_r(NULL, delimiter, &savept);

        i++;
    }
    result[i] = NULL;
    *argc = i;
    return result;
}