#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    printf("simple_shell$ ");
    fflush(stdout);
}

void run_shell() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        pid_t pid;
	display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char *args[2];
	    args[0] = command;
	    args[1] = NULL;

            if (execve(command, args, environ) == -1) {
                perror("./shell");
                _exit(EXIT_FAILURE);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);

        }
    }

    printf("Exiting shell\n");
}
