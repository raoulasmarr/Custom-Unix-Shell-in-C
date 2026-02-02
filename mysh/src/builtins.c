#include <string.h>
#include <stdlib.h>
#include "builtins.h"
#include <unistd.h>
#include <stdio.h>
	//1 = handled (builtin or noop)
	//0 = not a builtin
int handle_builtin(command *cmd){
    if(cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL){
    
    return 1;
    }
    else if (strcmp(cmd->argv[0],"exit")==0){
        exit(0);
       return 1;
    }
    else if (strcmp(cmd->argv[0],"cd")==0){
        const char *target = cmd->argv[1];
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
    else if (strcmp(cmd->argv[0],"export")==0){
        
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
    else if (strcmp(cmd->argv[0],"echo")==0){
        for(int i = 1; i <cmd->argc; i++){
        printf("%s ", cmd->argv[i]);
        }
        printf("\n");
        return 1;

    }
    return 0;






}
