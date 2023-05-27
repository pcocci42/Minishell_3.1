#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_commands_with_pipe(char* commands[], int num_commands, char **envp) {
    int i;
    int fd[2];
    int in = dup(STDIN_FILENO);

    for (i = 0; i < num_commands - 1; i++) {
        pipe(fd); // create a pipe

        if (fork() == 0) { // child process
            dup2(in, 0); // redirect stdin

            // If it's not the last command, redirect stdout to the write end of the pipe
            if (i != num_commands - 1)
                dup2(fd[1], 1); // redirect stdout

            close(fd[0]); // close unused read end of the pipe

            // Execute the command
            if (execve(commands[i], commands + i, envp) == -1) {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
        } else { // parent process
            wait(NULL); // wait for the child process to finish
            close(fd[1]); // close write end of the pipe
            in = fd[0]; // set the next input to the read end of the pipe
        }
    }

    // Execute the last command
    if (fork() == 0) { // child process
        dup2(in, 0); // redirect stdin

        // Execute the command
        if (execve(commands[i], commands + i, envp) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else { // parent process
        wait(NULL); // wait for the child process to finish
    }
}

int main(int argc, char *argv[], char **envp) {
    if (argc < 2) {
        printf("Usage: %s <command1> <command2> ... <commandN>\n", argv[0]);
        return 1;
    }

    run_commands_with_pipe(argv + 1, argc - 1, envp);

    return 0;
}