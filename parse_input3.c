/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/09 00:43:22 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//void    convert_dquote(t_cmd *cmd)
//{
//    int i;
//    int j;

//    j = 0;
//    i = 0;
//    {
//        while (cmd->cmd[i])
//        {
//            if (cmd->cmd[i] == '"' && cmd->squote == 0)
//            {   
//                if (cmd->cmd[i - 1] != '=')
//                    cmd->cmd[i] = ' ';
//                else
//                    cmd->cmd[i] = 19;
//                j = i -1;
//                i++;
//                cmd->squote = 0;
//                if (ft_chr(cmd->cmd, '"', i) == 0)
//                    cmd->dquote = 1;
//                while (cmd->cmd[i] != '"' && cmd->dquote == 1)
//                {
//                    if (cmd->cmd[i] == ' ')
//                        cmd->cmd[i] = 17;
//                    if (cmd->cmd[i] == '|')
//                        cmd->cmd[i] = 18;
//                    i++;
//                }
//                if (cmd->cmd[j] != '=')
//                    cmd->cmd[i] = ' ';
//                else
//                    cmd->cmd[i] = 19;
//                cmd->dquote = 0;
//            }
//            else if (cmd->cmd[i] == '\'' && cmd->dquote == 0)
//            {
//                if (cmd->cmd[i - 1] != '=')
//                    cmd->cmd[i] = ' ';
//                else
//                    cmd->cmd[i] = 19;
//                j = i -1;
//                i++;
//                cmd->dquote = 0;
//                if (ft_chr(cmd->cmd, '\'', i) == 0)
//                    cmd->squote = 1;
//                while (cmd->cmd[i] != '\'' && cmd->squote == 1)
//                {
//                    if (cmd->cmd[i] == ' ')
//                        cmd->cmd[i] = 17;
//                    if (cmd->cmd[i] == '|')
//                        cmd->cmd[i] = 18;
//                    if  (cmd->cmd[i] == '$')
//                        cmd->cmd[i] = 20;
//                    i++;
//                }
//                if (cmd->cmd[j] != '=')
//                    cmd->cmd[i] = ' ';
//                else
//                    cmd->cmd[i] = 19;
//                cmd->squote = 0;
//            }
//            i++;
//        }
//    }
//}

void	handle_dquote(t_cmd *cmd)
{	
	if (ft_chr(cmd->cmd, '"', cmd->ints->i + 1) == 0)
		cmd->dquote = 1;
	if (cmd->cmd[cmd->ints->i - 1] != '=' && cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->ints->j = cmd->ints->i -1;
	cmd->ints->i++;
	cmd->squote = 0;
	while (cmd->cmd[cmd->ints->i] != '"' && cmd->dquote == 1)
	{
		if (cmd->cmd[cmd->ints->i] == ' ')
			cmd->cmd[cmd->ints->i] = 17;
		if (cmd->cmd[cmd->ints->i] == '|')
			cmd->cmd[cmd->ints->i] = 18;
		if (cmd->cmd[cmd->ints->i] == 20)
			cmd->cmd[cmd->ints->i] = '$';
		cmd->ints->i++;
	}
	if (cmd->cmd[cmd->ints->j] != '=' && cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->dquote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->dquote = 0;
}

void	handle_squote(t_cmd *cmd)
{
	if (ft_chr(cmd->cmd, '\'', cmd->ints->i + 1) == 0)
		cmd->squote = 1;
	if (cmd->cmd[cmd->ints->i - 1] != '=' && cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->ints->j = cmd->ints->i -1;
	cmd->ints->i++;
	cmd->dquote = 0;
	while (cmd->cmd[cmd->ints->i] != '\'' && cmd->squote == 1)
	{
		if (cmd->cmd[cmd->ints->i] == ' ')
			cmd->cmd[cmd->ints->i] = 17;
		if (cmd->cmd[cmd->ints->i] == '|')
			cmd->cmd[cmd->ints->i] = 18;
		if (cmd->cmd[cmd->ints->i] == '$')
			cmd->cmd[cmd->ints->i] = 20;
		cmd->ints->i++;
	}
	if (cmd->cmd[cmd->ints->j] != '=' && cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = ' ';
	else if (cmd->squote == 1)
		cmd->cmd[cmd->ints->i] = 19;
	cmd->squote = 0;
}

void	convert_dquote(t_cmd *cmd)
{
	cmd->ints = malloc(sizeof(t_int));
	cmd->ints->j = 0;
	cmd->ints->i = 0;
	{
		while (cmd->cmd[cmd->ints->i])
		{
			if (cmd->cmd[cmd->ints->i] == '"' && cmd->squote == 0)
			{
				handle_dquote(cmd);
			}
			else if (cmd->cmd[cmd->ints->i] == '\'' && cmd->dquote == 0)
			{
				handle_squote(cmd);
			}
			cmd->ints->i++;
		}
	}
	free(cmd->ints);
}
