#ifndef PARSER_H
#define PARSER_H
#include "command.h"
#include "tokenizer.h"

command *parse_line(char *line);
void free_command(command *cmd);

#endif