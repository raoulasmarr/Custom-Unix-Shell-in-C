#include "executer.h"
#include "builtins.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Executes a non-builtin command.
/*
 * This function:
 *   - forks
 *   - child calls execvp
 *   - parent waits and stores status elsewhere
 */
void execute(command *cmd) {
    if(handle_builtin(cmd)==0){
    if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL) {
        return; 
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        execvp(cmd->argv[0], cmd->argv); // Replace the child process with the requested executable.
                                        // execvp searches PATH and passes argv to the new program.

        // If we got here, exec failed.
        // Match common shell behavior: 127 for "command not found", 126 for "found but not executable".
        int e = errno;
        if (e == ENOENT) {
            fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
            _exit(127);
        }
        if (e == EACCES) {
            fprintf(stderr, "%s: permission denied\n", cmd->argv[0]);
            _exit(126);
        }

        fprintf(stderr, "%s: %s\n", cmd->argv[0], strerror(e));
        _exit(126);
    }

    // Parent process: wait for child to finish
    int status = 0;
    while (waitpid(pid, &status, 0) < 0) {
        if (errno == EINTR) {
            continue; // interrupted by signal, retry
        }
        perror("waitpid");
        break;
    }
    }

}