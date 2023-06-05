/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/05 12:05:05 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    expand_var(t_cmd *cmd)
{

    int i = 0;
    int j = 0;
    while (cmd->box[i])
    {   
        j = 0;
        while (cmd->box[i][j])
        {   
            if (cmd->box[i][j][0] == '$')
                cmd->box[i][j] = getenv(cmd->box[i][j] + 1);
            j++;
        }
        i++;
    }
}


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

void    checking_redir(t_cmd *cmd, int i)
{
    int x;

    x = is_there_more_commands(cmd, cmd->box[i]);
    if (x > 0)
    {
        check_redirects_out(cmd, cmd->box[i]);
        cmd->box[i] = cmd->new_cmd;
        /* printf("%s\n", cmd->input);
        printf("%s\n", cmd->output); */
    }
}

void    open_pipes(int i, int num_pipes, int pipe_fds[num_pipes][2])
{
    while (i < num_pipes) 
    {
        if (pipe(pipe_fds[i]) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void    close_pipes(int i, int pipe_fds[i][2])
{
    if (i > 0) 
    {
        close(pipe_fds[i - 1][0]);
        close(pipe_fds[i - 1][1]);
    }
}

void    inter_exe(t_cmd *cmd, char **envp, int i)
{
    if (check_cmds(cmd->box[i], 0) == 1 &&  check_var_loop(cmd->box[i]) == 0 && is_valid_command(cmd->box[i][0]) == 0)
    {   
        expand_var(cmd);
        if (ft_strchr(cmd->box[i][0], '/'))
            execve((cmd->box[i][0]), cmd->box[i], environ);
        else
            execve(find_command_path(cmd->box[i][0]), cmd->box[i], environ);
        perror("execve");
    }
    else if (check_cmds(cmd->box[i], 0) == 0 ||  check_var_loop(cmd->box[i]) == 1)
        custom_commands(cmd, cmd->box[i], envp);
    else
    {
        printf("%s: command not found\n", cmd->box[i][0]);
        exit(0);
    }
}

void    error_fork(pid_t pid)
{
    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void    set_struct(t_exe *exe, int num_pipes)
{
    exe->input_fd = STDIN_FILENO;
    exe->output_fd = STDOUT_FILENO;
    exe->original_stdout = dup(STDOUT_FILENO);
    exe->last_command_index = num_pipes;
    exe->num_pipes = num_pipes;
}

void    redirect_input(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2])
{
    if (ft_strcmp(cmd->box[0][0], "<<") == 0) 
    {   
        exe->input_fd = open("heredoc_tmp.txt", O_RDONLY);
        cmd->f->write_in = 1;
        if (exe->input_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
    if (i == 0 && cmd->input != NULL) 
    {
        exe->input_fd = open(cmd->input, O_RDONLY);
        if (exe->input_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    } else if (i > 0 && cmd->f->write_in == 0) 
    {
        close(pipe_fds[i - 1][1]);
        exe->input_fd = pipe_fds[i - 1][0];
    }
    dup2(exe->input_fd, STDIN_FILENO);
    close(exe->input_fd);
}

void    redirect_output(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2])
{
    if (i == exe->last_command_index && cmd->output != NULL) 
    {
        if (cmd->f->append_out)
            exe->output_fd = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            exe->output_fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (exe->output_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
    else if (i == exe->last_command_index && cmd->output == NULL)
    {   
        exe->output_fd = exe->original_stdout;
    }
    else if (i < exe->last_command_index) 
    {
        close(pipe_fds[i][0]);
        exe->output_fd = pipe_fds[i][1];
    }
    dup2(exe->output_fd, STDOUT_FILENO);
    close(exe->output_fd);
}

void    child_process(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2], char **envp)
{
    redirect_input(cmd, exe, i, pipe_fds); // Redirect input
    redirect_output(cmd, exe, i, pipe_fds); // Redirect output
    inter_exe(cmd, envp, i); // Execute the command
    if (i > 0) 
        close(pipe_fds[i - 1][0]);
    if (i < exe->num_pipes) 
        close(pipe_fds[i][1]);
}

void    parent_wait(int num_pipes)
{
    int i;

    i = 0;
    while (i <= num_pipes) 
    {
        wait(NULL);
        i++;
    }
}

void execute_command(t_cmd *cmd, int num_pipes, char **envp) 
{
    t_exe exe;
    int pipe_fds[num_pipes][2];
    int i;
    
    set_struct(&exe, num_pipes);
    open_pipes(0, num_pipes, pipe_fds);
    i = 0;
    while (i <= num_pipes) 
    {   
        checking_redir(cmd, i);
        if (cmd->syntax_err == 1)
            return ; 
        exe.pid = fork();
        error_fork(exe.pid);
        if (exe.pid == 0) // Child process
            child_process(cmd, &exe, i, pipe_fds, envp);
        else // Parent process
            close_pipes(i, pipe_fds);
        i++;
    }
    parent_wait(num_pipes);
    dup2(exe.original_stdout, STDOUT_FILENO); // Restore the original stdout
    close(exe.original_stdout);
}

void handle_here_doc_input(const char* delimiter) {
    int input_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (input_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read lines from stdin until delimiter is encountered
    char* line;
    while ((line = readline("> ")) != NULL) {
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(input_fd, line, strlen(line));
        write(input_fd, "\n", 1);
        free(line);
    }
    close(input_fd);
}


