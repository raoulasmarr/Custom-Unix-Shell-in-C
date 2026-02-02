#include <string.h>
#include <stdlib.h>
#include "builtins.h"
#include <unistd.h>
#include <stdio.h>

// Handle built-in shell commands.
// Returns 1 if the command was handled internally (builtin or no-op),
// or 0 if the command should be executed as an external program.

int handle_builtin(command *cmd){
    if(cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL){ // Empty or invalid command check
    
    return 1;
    }
    // Exit the shell immediately
    else if (strcmp(cmd->argv[0],"exit")==0){
        exit(0);
       return 1;
    }
    // Change the shells current directory
    else if (strcmp(cmd->argv[0],"cd")==0){
        const char *target = cmd->argv[1];
        //If no directory is provided default is HOME
        if(target == NULL){
            target = getenv("HOME");
            if (target == NULL)
            {
                fprintf(stderr, "cd: HOME not set\n");
                return 1;
            }
            

        }
        if(chdir(target) == -1){
            perror("cd");
        }
    return 1;
    }
    //Print working directory
    else if (strcmp(cmd->argv[0],"pwd")==0){
        char pwd[1024];
        if(getcwd(pwd, sizeof(pwd)) != NULL){
            printf("%s\n", pwd);
        }
        else{
            perror("pwd");
        }
            return 1;

    }
    //set or display environment variables
    else if (strcmp(cmd->argv[0],"export")==0){
        // print all environment variables
        if(cmd->argv[1] ==NULL)
        {
            extern char **environ;
            char **position = environ;
            for(;*position;position++){
                fprintf(stdout,"%s\n",*position );
            }
            return 1;
        }
        else 
        {  
            for(int i = 1; i < cmd->argc; i++){
                char *temp = strdup(cmd->argv[i]);
                if(temp == NULL){
                    perror("export");
                    continue;
                }
                char *name = strtok(temp, "=");
                char *value = strtok(NULL, "=");

                if(name == NULL){
                    fprintf(stderr, "Invalid arguement");
                }
                else if (value == NULL)
                {
                    if(setenv(name, "", 1)){
                        perror("export");
                    }
                    

                }
                else{
                    if(setenv(name, value, 1)){
                        perror("export");
                    }
                    
                }
                free(temp);
                
            }
        }
        
        return 1;

    }
    //Remove environment variables form the shell environment
    else if (strcmp(cmd->argv[0],"unset")==0){
        for (int i = 1; i < cmd->argc; i++) {
            const char *name = cmd->argv[i];
            if (name == NULL) continue;

            if (unsetenv(name) == -1) {
                perror("unset");
            }
        }
        return 1;

    }
    //Prints arguments 
    else if (strcmp(cmd->argv[0],"echo")==0){
        for(int i = 1; i <cmd->argc; i++){
        printf("%s ", cmd->argv[i]);
        }
        printf("\n");
        return 1;

    }
    // not a built in command; should be passed to executer
    return 0;






}
