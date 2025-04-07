#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 100

// Function to execute a command
void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    // Split the input into tokens (words)
    token = strtok(input, " \t\r\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;  // Null-terminate the array of arguments

    if (args[0] == NULL) {
        return;  // If no command is entered
    }

    // If it's a built-in command (e.g., exit or cd)
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        // Change the directory
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) == -1) {
            perror("chdir failed");
        }
    } else {
        // Create a child process to run the command
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return;
        } else if (pid == 0) {
            // In the child process, execute the command
            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
                exit(1);  // Exit the child process if execution fails
            }
        } else {
            // In the parent process, wait for the child to finish
            int status;
            if (wait(&status) == -1) {
                perror("Wait failed");
            }
        }
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    // Main loop
    while (1) {
        // Display a prompt
        printf("<zerminal> ");
        
        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle the error if input can't be read (e.g., EOF or input error)
            if (feof(stdin)) {
                printf("\nEOF encountered. Exiting...\n");
                break;  // Exit on EOF (Ctrl+D)
            } else {
                perror("Error reading input");
                continue;
            }
        }

        // Execute the input command
        execute_command(input);
    }

    return 0;
}
