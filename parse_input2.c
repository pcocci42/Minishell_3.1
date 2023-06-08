/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/09 00:15:52 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_chr(char *cmd, char c, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	print_parsed_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->parsed[i])
	{
		printf("%s\n", cmd->parsed[i]);
		i++;
	}
}

void	print_parsed_box(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

void	convert(t_cmd *cmd)
{
	cmd->squote = 0;
	cmd->dquote = 0;
	convert_dquote(cmd);
	cmd->squote = 0;
	cmd->dquote = 0;
}

void	look_here_doc(t_cmd *cmd, int i, int j)
{
	while (cmd->box[i])
	{
		while (cmd->box[i][j])
		{
			if (ft_strcmp(cmd->box[i][j], "<<") == 0)
			{
				handle_here_doc_input(cmd->box[i][j + 1], cmd);
				if (j == 0)
					cmd->box[i][j] = NULL;
				else
				{
					j = 1;
					while (cmd->box[i][j])
						cmd->box[i][j] = NULL;
					cmd->f->write_in = 1;
					cmd->input = "heredoc_tmp.txt";
					break ;
				}
			}
			j++;
		}
		i++;
	}
}
