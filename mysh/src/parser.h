#ifndef PARSER_H
#define PARSER_H
#define MAX_ARGS 20
typedef struct{
    char **argv;
    int argc;
}command;

int initialize(command* cmd);
command *parse_line(char *line);
void free_command(command *cmd);

#endif