/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/30 12:40:29 by paolococci       ###   ########.fr       */
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

    cmd->input = NULL;
    cmd->output = NULL;
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
        ft_strcpy(cmd->output, parsed[i - 1]);
    }
    else if (cmd->f->re_in == 1)
    {
        cmd->input = malloc(strlen(parsed[i - 1]) + 1);
        ft_strcpy(cmd->input, parsed[i - 1]);
    }
    cmd->new_cmd[x + 1] = 0;
    //printf("%s\n", cmd->new_cmd[x + 1]);
}

void    check_redirects_out(t_cmd *cmd, char **parsed)
{
    int i;
    int j;
    int flag;

    i = 0;
    j = 0;
    flag = 0;
    while (parsed[i])
    {   
        if((!ft_strcmp(parsed[i], ">") || !ft_strcmp(parsed[i], "<") || !ft_strcmp(parsed[i], "<<") ||
        !ft_strcmp(parsed[i], ">>")) && flag == 0)
        {
            j = i;
            flag = 1;
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