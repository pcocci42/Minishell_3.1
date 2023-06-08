/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/08 21:34:24 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_export(t_cmd *cmd, char **parsed, char **envp)
{
	int	i;

	i = 0;
	if (ft_strcmp(parsed[0], "export") == 0 && (parsed[1] == NULL
			|| cmd->f->re_out == 1))
	{
		while (envp[i])
			printf("declare -x %s\n", envp[i++]);
	}
}

void	redir_flag(t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd->box[i][cmd->index->i_in], "<") == 0
		|| ft_strcmp(cmd->box[i][cmd->index->i_in], "<<") == 0)
		cmd->f->re_in = 1;
	if (ft_strcmp(cmd->box[i][cmd->index->i_out], ">") == 0)
		cmd->f->re_out = 1;
	else if (ft_strcmp(cmd->box[i][cmd->index->i_out], ">>") == 0)
	{
		cmd->f->re_out = 1;
		cmd->f->append_out = 1;
	}
}

void	many_redir(t_cmd *cmd, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(cmd->box[i][cmd->index->i_in - 1]);
	cmd->new_cmd = malloc((sizeof(char *)) * (len + 1));
	while (j < cmd->index->i_in)
	{
		cmd->new_cmd[j] = cmd->box[i][j];
		j++;
	}
	cmd->new_cmd[j] = NULL;
	cmd->input = malloc((sizeof(char *))
			* ft_strlen(cmd->box[i][cmd->index->i_in + 1]));
	cmd->output = malloc((sizeof(char *))
			* ft_strlen(cmd->box[i][cmd->index->i_out + 1]));
	ft_strcpy(cmd->input, cmd->box[i][cmd->index->i_in + 1]);
	ft_strcpy(cmd->output, cmd->box[i][cmd->index->i_out + 1]);
	redir_flag(cmd, i);
}
