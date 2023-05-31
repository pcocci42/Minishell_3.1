/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/30 11:36:12 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int    is_there_more_commands(t_cmd *cmd, char **parsed)
{
    int i;

    i = 0;
    while(parsed[i])
    {
        if(strcmp(parsed[i], "<") == 0)
        {   
            cmd->f->re_in = 1;
            return(i);
        }
        if(strcmp(parsed[i], ">") == 0)
        {   
            cmd->f->re_out = 1;
            return(i);
        }
        if(strcmp(parsed[i], "<<") == 0)
        {
            cmd->f->re_in = 1;
            //cmd->f->append_out = 1;
            return(i);
        }
        if(strcmp(parsed[i], ">>") == 0)
        {
            cmd->f->re_out = 1;
            cmd->f->append_out = 1;
            return(i);
        }
        i++;
    }
    return(0);
}

void    ft_strstr(t_cmd *cmd, int j, int i, char **parsed)
{
    int x;

    /* cmd->input = NULL;
    cmd->output = NULL; */
    x = 0;
    while (x < j)
    {
        cmd->new_cmd[x] = malloc(strlen(parsed[x]) + 1);
        ft_strcpy(cmd->new_cmd[x], parsed[x]);
        x++;
    }
    if (cmd->f->re_out == 1)
    {
        cmd->output = malloc(strlen(parsed[i - 1]) + 1);
        //printf("%s\n", cmd->parsed[i-1]);
        ft_strcpy(cmd->output, parsed[i - 1]);
        //printf("%s\n", cmd->output);
    }
    else if (cmd->f->re_in == 1)
    {
        cmd->input = malloc(strlen(parsed[i - 1]) + 1);
        ft_strcpy(cmd->input, parsed[i - 1]);
        printf("%s\n", cmd->input);
    }
    /* cmd->new_cmd[x] = malloc(strlen(cmd->parsed[i - 1]) + 1);
    strcpy(cmd->new_cmd[x], cmd->parsed[i - 1]); */
    cmd->new_cmd[x] = NULL;
}

void    check_redirects_out(t_cmd *cmd, char **parsed)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 0;
    flag = 0;
    while (cmd->parsed[i])
    {   
        if((!ft_strcmp(parsed[i], ">") || !ft_strcmp(parsed[i], "<") || !ft_strcmp(parsed[i], "<<") ||
        !ft_strcmp(parsed[i], ">>")) && flag == 0)
        {
            j = i;
            flag = 1;
            
            //i++;
        }
        else if((!ft_strcmp(parsed[i], ">") || !ft_strcmp(parsed[i], "<") || !ft_strcmp(parsed[i], "<<") ||
        !ft_strcmp(parsed[i], ">>")) && flag == 1)
        {   
            cmd->syntax_err =  1;
            break ;
        }
        i++;
    }
    cmd->new_cmd = malloc((i + 1) * sizeof(char *));
    ft_strstr(cmd, j, i, parsed);
}

void    process_input(t_cmd *cmd, char **parsed)
{
        // flag_checker(cmd);
        // flag_checker2(cmd);
        // print_flags(cmd);
        int i;

        i = is_there_more_commands(cmd, parsed);
        check_redirects_out(cmd, parsed);
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
        handle_var(parsed, cmd);
        int j;
        j = 0;
        
        if (i == 0)
        {
            while(parsed[i])
                i++;
            if (check_cmds(parsed, j) == 0)
                custom_commands(cmd,j,i);
            // else if ((check_cmds(cmd->parsed) != 0) || check_exe(cmd->parsed) == 1)
            else
            {   
                //set_in_out(cmd);
                printf("%s\n", cmd->output);
                execute_command(parsed, cmd->input, cmd->output, cmd->f->append_out);
                printf("%s\n", cmd->input);
                if (cmd->input)
                    free(cmd->input);
                if (cmd->output)
                    free(cmd->output);
            }
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
                    /* int x = 0;
                    while (cmd->new_cmd[x])
                    {
                        printf("%s\n", cmd->new_cmd[x]);
                        x++;
                    } */
                    //printf("0\n");
                    execute_command(cmd->new_cmd,cmd->input, cmd->output, cmd->f->append_out);
                    //printf("1");
                    if (cmd->input)
                        free(cmd->input);
                    if (cmd->output)
                        free(cmd->output);
                }
            }
            
        }
        flag_init(cmd->f);
        // flag_init(cmd->f); reinizzializzare i valori nel caso ma non i dup!!! (ci serve stdin e stdout originali)
}


void execute_command(char** args, char* input_file, char* output_file, int append_mode) 
{
    pid_t pid = fork();
    char    *envp[] = {"PATH=/bin", 0};
    char command[100];
    
   //printf("2");
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
        //printf("3");
        if (output_file != NULL) {
            printf("entro qui\n");
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
        if (ft_strcmp(args[0], "grep") == 0)
            exe_cmd_usr(args, command, envp);
        else if (check_exe(args) == 0 && ft_strcmp(args[0], "grep") != 0) //command in /bin/ 
            exe_basic_cmd(args, command, envp);
        
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, &g_exitstatus, 0);
    }
}
