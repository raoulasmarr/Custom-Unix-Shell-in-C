#include <parser.h>
#include <stdio.h>
#include <string.h>

int initialize(command* cmd){
    cmd->argv = calloc(MAX_ARGS + 1, sizeof(char*));
    if(cmd->argv == NULL){
        return -1;
    }
    cmd->argc = 0;
    return 0;
}
command *parse_line(char* line){
    int i = 0;
    int length = 0;
    char * word = NULL;
    command* result = calloc(1, sizeof(command));
    initialize(result);
    
    while(line[i] != '\n'){
        if(line[i] == ' '){
            word = strndup(&line[i-length], length);
            length = 0;
            result->argv[result->argc++]= word;
        }
        else{
            length++;
        }
        i++;
    }
    return &result;

}
    

