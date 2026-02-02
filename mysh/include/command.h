#ifndef COMMAND_H
#define COMMAND_H
#define MAX_ARGS 128

typedef struct command{
    char **argv;
    int argc;
}command;

#endif