/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/23 18:43:08 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_export(t_cmd *cmd, char **parsed, char **envp)
{
	int	i;
	(void)envp;

	i = 0;
	if (ft_strcmp(parsed[0], "export") == 0 && (parsed[1] == NULL
			|| cmd->f->re_out == 1))
	{
		while (cmd->cpy_env[i])
			printf("declare -x %s\n", cmd->cpy_env[i++]);
	}
}

void	redir_flag(t_cmd *cmd, int i, int j)
{	
	int x;

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
}

void	many_redir(t_cmd *cmd, int i)
{
	int	j;
	int	len;
	char	new_cmd[250][250];

	j = 0;
	len = ft_strlen(cmd->box[i][cmd->index->i_in - 1]);
	//cmd->new_cmd = malloc((sizeof(char *)) * (len + 1));
	while (j < cmd->index->i_in)
	{
		//cmd->new_cmd[j] = cmd->box[i][j];
		ft_strcpy(new_cmd[j], cmd->box[i][j]);
		ft_strcpy(cmd->box[i][j], new_cmd[j]);
		j++;
	}
	// cmd->box[i][j] = NULL;
	// printf("%s\n", cmd->box[i][j]);
	cmd->input = malloc((sizeof(char *))
			* ft_strlen(cmd->box[i][cmd->index->i_in + 1]));
	cmd->output = malloc((sizeof(char *))
			* ft_strlen(cmd->box[i][cmd->index->i_out + 1]));
	ft_strcpy(cmd->input, cmd->box[i][cmd->index->i_in + 1]);
	ft_strcpy(cmd->output, cmd->box[i][cmd->index->i_out + 1]);
	redir_flag(cmd, i, j);
}

char	*ft_getenv(char *var, t_cmd *cmd)
{	
	int i;
	char	*name;
	char	*cnt;

	i = 0;
	while (cmd->cpy_env[i])
	{	
		name = take_var(cmd->cpy_env[i]);
		if (ft_strcmp(name, var) == 0)
		{
			cnt = getcnt(cmd->cpy_env[i], 0, 0);
			return (cnt);
			break ;
		}
		i++;
	}
	return (NULL);
}

void	ft_done(t_cmd *cmd)
{
	free(cmd->cmd);
	free(cmd->shell_prompt);
	free(cmd->index);
	free(cmd);
	exit(g_exitstatus);
}