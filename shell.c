#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 100

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
	int is_piped = isatty(STDIN_FILENO) == 0;
	display_prompt(is_piped);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1) {
            perror(executable_name);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char *args[2];
	    args[0] = command;
	    args[1] = NULL;

            if (execve(command, args, environ) == -1) {
                perror(executable_name);
                _exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);

        }
    }
}
