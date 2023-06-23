/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/23 17:56:57 by pcocci           ###   ########.fr       */
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

void	realloc_env(t_cmd *cmd, int i)
{
	char **cpy;
	int j;

	cpy = malloc((sizeof(char *)) * (i + 1));
	j = 0;
	while (cmd->cpy_env[j])
	{
		cpy[j] = malloc(sizeof(char) * (ft_strlen(cmd->cpy_env[j]) + 1));
		ft_strcpy(cpy[j], cmd->cpy_env[j]);
		j++;
	}
	free_envp(cmd);
	cpy[j] = NULL;
	copy_envp2(cmd, cpy, j);
	free_dpointer(cpy);
}

void	unset_update(t_cmd *cmd, int i)
{
	int		index;
	char	**tmp;

	index = 0;
	while (cmd->cpy_env[index])
		index++;
	tmp = malloc(((sizeof(char *)) * (index)));
	index = 0 ;
	while (index < i)
	{
		tmp[index] = ft_strdup(cmd->cpy_env[index]);
		index++;
	}
	while (cmd->cpy_env[i + 1])
	{
		tmp[i] = ft_strdup(cmd->cpy_env[i + 1]);
		i++;
	}
	tmp[i] = NULL;
	copy_envp(cmd, tmp);
	free_dpointer(tmp);
}