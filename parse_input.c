/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/24 17:08:12 by lmasetti         ###   ########.fr       */
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

void    parsed_quotes(t_cmd *cmd)
{
    cmd->squote = 0;
    cmd->dquote = 0;
    convert_dquote(cmd);
    cmd->parsed = ft_split(cmd->cmd, ' ');
    //print_parsed_quotes(cmd);
    cmd->squote = 0;
    cmd->dquote = 0;
}

void    parse_input(t_cmd *cmd)
{

    parsed_quotes(cmd);
}