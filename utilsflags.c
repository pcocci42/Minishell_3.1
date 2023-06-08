/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:27:05 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/09 00:15:15 by paolococci       ###   ########.fr       */
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
}

void	free_box(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->box[i])
	{
		while (cmd->box[i][j])
		{
			free(cmd->box[i][j]);
			j++;
		}
		i++;
	}
	/* i = 0;
	while (cmd->box[i])
	{
		free(cmd->box[i]);
		i++;
	} */
	free(cmd->box);
}

void	free_altro(t_cmd *cmd)
{
	free(cmd->f);
	free(cmd->input);
	free(cmd->output);
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
	free(dpoint);
}
