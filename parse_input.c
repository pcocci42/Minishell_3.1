/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/31 14:33:41 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int   ft_chr(char *cmd, char c, int i)
{
    while (cmd[i])
    {
        if (cmd[i] == c)
            return (0);
        i++;
    }
    return (1);
}

void    convert_dquote(t_cmd *cmd)
{
    int i;

    i = 0;
    {
        while (cmd->cmd[i])
        {
            if (cmd->cmd[i] == '"' && cmd->squote == 0)
            {   
                cmd->cmd[i] = ' ';
                i++;
                cmd->squote = 0;
                if (ft_chr(cmd->cmd, '"', i) == 0)
                    cmd->dquote = 1;
                while (cmd->cmd[i] != '"' && cmd->dquote == 1)
                {
                    if (cmd->cmd[i] == ' ')
                        cmd->cmd[i] = 17;
                    if (cmd->cmd[i] == '|')
                        cmd->cmd[i] = 18;
                    i++;
                }
                cmd->cmd[i] = ' ';
                cmd->dquote = 0;
            }
            else if (cmd->cmd[i] == '\'' && cmd->dquote == 0)
            {
                cmd->cmd[i] = ' ';
                i++;
                cmd->dquote = 0;
                if (ft_chr(cmd->cmd, '\'', i) == 0)
                    cmd->squote = 1;
                while (cmd->cmd[i] != '\'' && cmd->squote == 1)
                {
                    if (cmd->cmd[i] == ' ')
                        cmd->cmd[i] = 17;
                    if (cmd->cmd[i] == '|')
                        cmd->cmd[i] = 18;
                    if  (cmd->cmd[i] == '$')
                        cmd->cmd[i] = 20;
                    i++;
                }
                cmd->cmd[i] = ' ';
                cmd->squote = 0;
            }
            i++;
        }
    }
}

void    print_parsed_quotes(t_cmd *cmd)
{   
    int i;

    i = 0;
    while (cmd->parsed[i])
    {
        printf("%s\n", cmd->parsed[i]);
        i++;
    }
}

void    print_parsed_box(t_cmd *cmd)
{   
    int i;
    i = 0;
    int j = 0;
    //printf("%d\n", cmd->nbr_pipe);
    while (cmd->box[i])
    {   
        j = 0;
        while (cmd->box[i][j])
        {
            printf("%s\n", cmd->box[i][j]);
            j++;
        } 
        i++;
    }
}

void    convert(t_cmd *cmd)
{
    cmd->squote = 0;
    cmd->dquote = 0;
    convert_dquote(cmd);
    cmd->squote = 0;
    cmd->dquote = 0;
}

void    count_pipes(t_cmd *cmd)
{   
    int i;

    i = 0;
    cmd->nbr_pipe = 0;
    while (cmd->cmd[i])
    {
        if (cmd->cmd[i] == '|')
            cmd->nbr_pipe++;
        i++;
    }
}

void    split_pipes(t_cmd *cmd)
{   
    int i;
    char **split_pipes;
    i = 0;
    split_pipes = ft_split(cmd->cmd, '|');
    cmd->box = malloc((sizeof(char **)) * (cmd->nbr_pipe + 2));
    while (split_pipes[i])
    {
        cmd->box[i] = ft_split(split_pipes[i], ' ');
        i++;
    }
    /* printf("%d\n", i); */
    cmd->box[i] = NULL;
    //printf("%s\n", cmd->box[i][0]);
    i = 0;
    while (split_pipes[i])
    {
        free(split_pipes[i]);
        i++;
    }
    free(split_pipes);
}

void    variables(t_cmd *cmd, char ***box)
{   
    int i;

    i = 0;
    while (box[i])
    {   
        //printf("maybe\n");
        handle_var(box[i], cmd);
        i++;
    }
}

void    parse_input(t_cmd *cmd, char **envp)
{   
    //envp = NULL;
    convert(cmd);
    count_pipes(cmd);
    split_pipes(cmd);
    //print_parsed_box(cmd);
    //print_envp2(envp);
    //printf("###########################\n");
    look_var(cmd, envp);
    //printf("###########################\n");
    //print_envp2(envp);
    flag_init(cmd->f);
    cmd->output = NULL;
    cmd->input = NULL;
    execute_command(cmd->box, cmd, cmd->nbr_pipe, envp);
    cmd->output = NULL;
    cmd->input = NULL;
    flag_init(cmd->f);
}