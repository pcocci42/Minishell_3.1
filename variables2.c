/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/21 16:58:27 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	new_cmd(t_cmd *cmd, int i)
{	
	int j;
	int x;

	j = 0;
	while (cmd->new_cmd[j])
	{
		ft_strcpy(cmd->box[i][j], cmd->new_cmd[j]);
		j++;
	}
	x = j;
	while(cmd->box[i][j])
		j++;
	while(j>x)
	{
		free(cmd->box[i][j]);
		j--;
	}
	free(cmd->box[i][j]);
	cmd->box[i][j] = NULL;
	free_dpointer(cmd->new_cmd);
}

void	many_cmd(t_cmd *cmd, int i)
{
	int j;
	(void)i;

	j = 0;
	while (cmd->new_cmd[j])
	{
		printf("%s\n", cmd->new_cmd[j]);
		//free_dpointer(cmd->box[i]);
		j++;
	}
	free_dpointer(cmd->new_cmd);
	//cmd->box[i] = cmd->new_cmd;
	//free_dpointer(cmd->box[i]);
}