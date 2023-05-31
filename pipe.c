/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/31 14:14:09 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char* find_command_path(const char* command) {
    char* path_env = getenv("PATH");
    if (path_env == NULL) {
        printf("Error: PATH environment variable not set.\n");
        return NULL;
    }

    char* path = strdup(path_env);
    if (path == NULL) {
        perror("strdup");
        return NULL;
    }

    char* dir = strtok(path, ":");
    while (dir != NULL) {
        char* full_path = (char*)malloc(strlen(dir) + strlen(command) + 2);
        if (full_path == NULL) {
            perror("malloc");
            free(path);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0) {
            free(path);
            return full_path;
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}

void execute_command(char*** commands, t_cmd *cmd, int num_pipes, char **envp) 
{
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    int original_stdout = dup(STDOUT_FILENO);
    int last_command_index = num_pipes;

    int pipe_fds[num_pipes][2];
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipe_fds[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i <= num_pipes; i++) 
    {
        /* handle_var(cmd->box[i], cmd);
        if (cmd->var_count > 0)
            return; */
        int x = is_there_more_commands(cmd, cmd->box[i]);
        if (x > 0)
        {
            printf("%d\n", x);
            check_redirects_out(cmd, cmd->box[i]);
            cmd->box[i] = cmd->new_cmd;
        }
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Redirect input
            if (i == 0 && cmd->input != NULL) {
                input_fd = open(cmd->input, O_RDONLY);
                if (input_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
            } else if (i > 0) {
                close(pipe_fds[i - 1][1]);
                input_fd = pipe_fds[i - 1][0];
            }

            dup2(input_fd, STDIN_FILENO);
            close(input_fd);

            // Redirect output
            if (i == last_command_index && cmd->output != NULL) {
                if (cmd->f->append_out)
                    output_fd = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    output_fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (output_fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
            } else if (i == last_command_index && cmd->output == NULL) {
                output_fd = original_stdout;
            } else if (i < num_pipes) {
                close(pipe_fds[i][0]);
                output_fd = pipe_fds[i][1];
            }

            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);

            // Execute the command
            if (check_cmds(cmd->box[i], 0) == 1 && check_var_loop(cmd->box[i]) == 0 && is_valid_command(cmd->box[i][0]) == 0)
            {
                execve(find_command_path(commands[i][0]), commands[i], envp);
                perror("execve");
            }
            else
            {   
                //mrintf("qiui\n");
                custom_commands(cmd, cmd->box[i]);
            }
            //exit(EXIT_FAILURE);
        } else {
            // Parent process

            if (i > 0) {
                close(pipe_fds[i - 1][0]);
                close(pipe_fds[i - 1][1]);
            }
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i <= num_pipes; i++) {
        wait(NULL);
    }

    // Restore the original stdout
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
}

