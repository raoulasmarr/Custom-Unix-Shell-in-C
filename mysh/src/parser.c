#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"


command *parse_line(char* line){
    command *result = calloc(1, sizeof(command));
    if(!result) return NULL;
    result->argv = tokenize(line, &result->argc);
    return result;

}
void free_command(command *cmd){
    for(int i =0; cmd->argv[i] != NULL; i++){
        free(cmd->argv[i]);
    }
    free(cmd->argv);
}
    


