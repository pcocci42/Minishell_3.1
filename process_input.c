/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/25 16:15:17 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int    is_there_more_commands(t_cmd *cmd)
{
    int i;

    i = 0;
    while(cmd->parsed[i])
    {
        if(strcmp(cmd->parsed[i], "<") == 0)
        {   
            cmd->f->re_in = 1;
            return(i);
        }
        if(strcmp(cmd->parsed[i], ">") == 0)
        {   
            cmd->f->re_out = 1;
            return(i);
        }
        if(strcmp(cmd->parsed[i], "<<") == 0)
        {
            cmd->f->re_in = 1;
            //cmd->f->append_out = 1;
            return(i);
        }
        if(strcmp(cmd->parsed[i], ">>") == 0)
        {
            cmd->f->re_out = 1;
            cmd->f->append_out = 1;
            return(i);
        }
        if(strcmp(cmd->parsed[i], "|") == 0)
            return(i);
        i++;
    }
    return(0);
}

void    ft_strstr(t_cmd *cmd, int j, int i)
{
    int x;

    cmd->input = NULL;
    cmd->output = NULL;
    x = 0;
    while (x < j)
    {
        cmd->new_cmd[x] = malloc(strlen(cmd->parsed[x]) + 1);
        strcpy(cmd->new_cmd[x], cmd->parsed[x]);
        x++;
    }
    if (cmd->f->re_out == 1)
    {
        cmd->output = malloc(strlen(cmd->parsed[i - 1]) + 1);
        strcpy(cmd->output, cmd->parsed[i - 1]);
    }
    else if (cmd->f->re_in == 1)
    {
        cmd->input = malloc(strlen(cmd->parsed[i - 1]) + 1);
        strcpy(cmd->input, cmd->parsed[i - 1]);
    }
    /* cmd->new_cmd[x] = malloc(strlen(cmd->parsed[i - 1]) + 1);
    strcpy(cmd->new_cmd[x], cmd->parsed[i - 1]); */
    cmd->new_cmd[x + 1] = NULL;
}

/* void    check_redirects_out(t_cmd *cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd->parsed[i])
    {   
        if(ft_strcmp(cmd->parsed[i], "|") == 0)
            break ;
        if(ft_strcmp(cmd->parsed[i], ">>") == 0)
            break ;
        if(ft_strcmp(cmd->parsed[i], "<<") == 0)
            break ;
        if(ft_strcmp(cmd->parsed[i], "<") == 0)
            break ;
        if (ft_strcmp(cmd->parsed[i], ">") == 0)
        {
            j = i;
        }
        i++;
    }
    cmd->new_cmd = malloc((i + 1) * sizeof(char *));
    ft_strstr(cmd, j, i);
} */

void    check_redirects_out(t_cmd *cmd)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 0;
    flag = 0;
    while (cmd->parsed[i])
    {   
        if((!ft_strcmp(cmd->parsed[i], ">") || !ft_strcmp(cmd->parsed[i], "<") || !ft_strcmp(cmd->parsed[i], "<<") ||
        !ft_strcmp(cmd->parsed[i], ">>")) && flag == 0)
        {
            j = i;
            flag = 1;
            
            //i++;
        }
        else if((!ft_strcmp(cmd->parsed[i], ">") || !ft_strcmp(cmd->parsed[i], "<") || !ft_strcmp(cmd->parsed[i], "<<") ||
        !ft_strcmp(cmd->parsed[i], ">>")) && flag == 1)
        {   
            cmd->syntax_err =  1;
            break ;
        }
        i++;
    }
    cmd->new_cmd = malloc((i + 1) * sizeof(char *));
    ft_strstr(cmd, j, i);
}

void    process_input(t_cmd *cmd)
{
        // flag_checker(cmd);
        // flag_checker2(cmd);
        // print_flags(cmd);
        int i;

        i = is_there_more_commands(cmd);
        check_redirects_out(cmd);
        if (cmd->syntax_err == 1)
        {
            printf("Syntax error\n");
            cmd->syntax_err = 0;
            return ;
        }
        /* while (cmd->new_cmd[i])
        {
            printf("%s\n", cmd->new_cmd[i]);
            i++;
        } */
        handle_var(cmd->parsed, cmd);
        int j;
        j = 0;
        
        if (i == 0)
        {
            while(cmd->parsed[i])
                i++;
            if (check_cmds(cmd->parsed, j) == 0)
                custom_commands(cmd,j,i);
            // else if ((check_cmds(cmd->parsed) != 0) || check_exe(cmd->parsed) == 1)
            else
                exeArgs(cmd,j,i);
        }
        else 
        {
            // come dividiamo il parsed per eseguire i comandi vari?
            // facciamo vari array da mandare in pasto a execve?
            {
                if (check_cmds(cmd->new_cmd, j) == 0)
                    custom_commands(cmd,j,i);
                else
                {   
                    execute_command(cmd->new_cmd,cmd->input, cmd->output, cmd->f->append_out);
                    free(cmd->input);
                    free(cmd->output);
                }
                flag_init(cmd->f);
            }
            
        }
        // flag_init(cmd->f); reinizzializzare i valori nel caso ma non i dup!!! (ci serve stdin e stdout originali)
}

void execute_command(char** args, char* input_file, char* output_file, int append_mode) 
{
    pid_t pid = fork();
    char    *envp[] = {"PATH=/bin", 0};
    char command[100];
    
    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Redirect input if an input file is specified
        if (input_file != NULL) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Redirect output if an output file is specified
        if (output_file != NULL) {
            int fd_out;
            if (append_mode)
                fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd_out == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if (check_exe(args) == 0) //command in /bin/ 
            exe_basic_cmd(args, command, envp);
        
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child to finish
    }
}
