/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dochelp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:11:50 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/09 00:19:30 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	out_heredoc_help(t_cmd *cmd, int i, int j, int count)
{
	while (cmd->box[i])
	{
		while (cmd->box[i][j])
		{
			if ((ft_strcmp(cmd->box[i][j], "<<") == 0)
				|| (ft_strcmp(cmd->box[i][j], ">") == 0)
				|| (ft_strcmp(cmd->box[i][j], ">>") == 0))
			{
				if ((ft_strcmp(cmd->box[i][j], ">") == 0)
					|| (ft_strcmp(cmd->box[i][j], ">>") == 0))
				{
					cmd->hd_j = j + 1;
					cmd->hd_i = i;
					if (ft_strcmp(cmd->box[i][j], ">>") == 0)
						cmd->f->append_out = 1;
				}
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	out_heredoc(t_cmd *cmd)
{	
	int	len;

	len = 0;
	if (out_heredoc_help(cmd, 0, 0, 0) == 2)
	{	
		len = ft_strlen(cmd->box[cmd->hd_i][cmd->hd_j]);
		cmd->output = malloc((sizeof(char *)) * (len + 1));
		cmd->f->re_out = 1;
		ft_strcpy(cmd->output, cmd->box[cmd->hd_i][cmd->hd_j]);
	}
}

int	in_fd(t_cmd *cmd)
{
	int	input_fd;

	if (cmd->output != NULL && cmd->f->re_out == 1 && cmd->f->append_out == 0)
		input_fd = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->output != NULL && cmd->f->re_out == 1
		&& cmd->f->append_out == 1)
		input_fd = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		input_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (input_fd);
}

void	write_line(int input_fd, char *line)
{
	write(input_fd, line, ft_strlen(line));
	write(input_fd, "\n", 1);
	free(line);
}
