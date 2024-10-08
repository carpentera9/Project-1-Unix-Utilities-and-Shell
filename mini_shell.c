#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

void tokenize_input(char *line, char **args) {
    char *token;
    int index = 0;

    token = strtok(line, " \t\n");
    while (token != NULL && index < MAX_ARGS - 1) {
        args[index++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[index] = NULL;
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nExiting shell.\n");
            break;
        }

        if (line[0] == '\n') {
            continue;
        }

        tokenize_input(line, args);

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
