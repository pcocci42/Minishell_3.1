/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:27:05 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/21 18:06:44 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	flag_init(t_cmd *cmd)
{
	cmd->f->append_out = 0;
	cmd->f->d_quote = 0;
	cmd->f->pipe = 0;
	cmd->f->quote = 0;
	cmd->f->re_in = 0;
	cmd->f->re_out = 0;
	cmd->f->write_in = 0;
	cmd->syntax_err = 0;
	cmd->hd_j = 0;
	cmd->hd_i = 0;
}

void	free_box(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{	
		j = 0;
		{
			while (cmd->box[i][j])
			{
				{
					free(cmd->box[i][j]);
				}
				j++;
			}
		}
		i++;
	}
	i = 0;
	while (cmd->box[i])
	{	
		free(cmd->box[i]);
		i++;
	}
	free(cmd->box[i]);
	free(cmd->box);
}

void	free_altro(t_cmd *cmd)
{
	free(cmd->f);
	free_box(cmd);
}

void	free_dpointer(char **dpoint)
{
	int	i;

	i = 0;
	if (!dpoint)
		return ;
	while (dpoint[i])
	{
		free(dpoint[i]);
		i++;
	}
	free(dpoint[i]);
	free(dpoint);
}
