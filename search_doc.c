/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 00:18:27 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/09 12:19:47 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	scorri_cmd(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		cmd->cmd++;
		i++;
	}
}

int	search_helper(t_cmd *cmd, int i, int flag)
{
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '<')
		{
			if (ft_chr(cmd->cmd, '<', i + 1) == 0)
			{
				flag = 1;
				return (flag);
			}
		}
		i++;
	}
	return (0);
}

void	search_here(t_cmd *cmd)
{	
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (cmd->cmd[i])
		i++;
	while (i >= 0)
	{
		if (ft_chr(cmd->cmd, '|', i) == 0)
		{	
			j = i + 1;
			break ;
		}
		i--;
	}
	flag = search_helper(cmd, i, flag);
	if (flag == 1)
		scorri_cmd(cmd, j);
}
