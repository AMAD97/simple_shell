#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void display_prompt() {
    printf("#cisfun$ ");
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[2]; /* Assuming commands have one word only */

    while (1) {
        display_prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break; /* Exit on Ctrl+D (EOF) */
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove newline character */

        args[0] = buffer;
        args[1] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("Error forking");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            if (execve(args[0], args, NULL) == -1) {
                perror(args[0]); /* Print error message with program name */
            }
            exit(EXIT_FAILURE); /* If execve fails */
        } else {
            /* Parent process */
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}
