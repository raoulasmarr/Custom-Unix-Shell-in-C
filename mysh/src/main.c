#include "parser.h"
#include "executer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
    char *line = NULL;
    size_t len = 0;

    while(1){
        printf("mysh> ");
        fflush(stdout);

        if(getline(&line, &len, stdin) == -1){
            printf("\n");
            break;
        }

        command *cmd = parse_line(line);
        if(cmd == NULL) continue;
        execute(cmd);
        free_command(cmd);

    }
    free(line);
    return 0;
}