/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:33:41 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/23 18:06:36 by pcocci           ###   ########.fr       */
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
		printf("i :%d\n", i);
		while (cmd->box[i][j])
		{	
			printf("j: %d\n", j);
			printf("box: %s\n", cmd->box[i][j]);
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
	int x;

	x = 0;
	while (cmd->box[i])
	{	
		j = 0;
		while (cmd->box[i][j])
		{
			if (ft_strcmp(cmd->box[i][j], "<<") == 0)
			{	
				cmd->f->write_in = 1;
				handle_here_doc_input(cmd->box[i][j + 1], cmd, j, i);
				if (j == 0)
					cmd->box[i][j] = NULL;
				else
				{
					j = 1;
					x = j;
					while (cmd->box[i][x])
					{
						free(cmd->box[i][x]);
						cmd->box[i][x] = NULL;
						x++;
					}
					cmd->input = "heredoc_tmp.txt";
					break ;
				}
			}
			j++;
		}
		i++;
	}
}
