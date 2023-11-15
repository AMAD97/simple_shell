#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10


void display_prompt(int is_piped) {
    if (!is_piped) {
        printf("simple_shell$ ");
        fflush(stdout);
    }
}

void run_shell(const char *executable_name) {
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        pid_t pid;
    	char *args[MAX_ARGS + 1];
    	int arg_count;
	char *token;

	int is_piped = isatty(STDIN_FILENO) == 0;
	display_prompt(is_piped);

        if (fgets(command, sizeof(command), stdin) == NULL) {
	        if (!is_piped) {
        	    printf("\n");
        	}
       		break;
    	}


        command[strcspn(command, "\n")] = '\0';

	token = strtok(command, " ");
        arg_count = 0;
	

        while (token != NULL && arg_count < MAX_ARGS) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }

        while (token != NULL && arg_count < MAX_ARGS) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }

        args[arg_count] = NULL;
        
	if (strcmp(args[0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        }


        pid = fork();

        if (pid == -1) {
            perror(executable_name);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror(args[0]);
                _exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
	    
        }
    }
}
