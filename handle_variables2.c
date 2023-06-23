/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/21 13:55:53 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	up_environ(char *current)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;

	i = 0;
	flag = 0;
	var = take_var(current);
	name = take_var(environ[i]);
	while (environ[i])
	{
		if (ft_strcmp(name, var) != 0)
			i++;
		else
		{	
			flag = 1;
			break ;
		}
	}
	free(var);
	free(name);
	environ[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(environ[i], current);
	if (flag == 0)
		environ[i + 1] = NULL;
}

void	up_envp(char *current, char **envp)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;

	i = 0;
	flag = 0;
	var = take_var(current);
	name = take_var(envp[i]);
	while (envp[i])
	{
		if (ft_strcmp(name, var) != 0)
			i++;
		else
		{	
			flag = 1;
			break ;
		}
	}
	free(var);
	free(name);
	envp[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(envp[i], current);
	if (flag == 0)
		envp[i + 1] = NULL;
}

void	look_var_envp(t_cmd *cmd, char **envp)
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
			if (check_var(cmd->box[i][j]) == 1)
			{
				up_envp(cmd->box[i][j], envp);
			}
			j++;
		}
		i++;
	}
}

void	look_var(t_cmd *cmd, char **envp)
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
			if (check_var(cmd->box[i][j]) == 1)
			{
				up_envp(cmd->box[i][j], envp);
			}
			j++;
		}
		i++;
	}
}
