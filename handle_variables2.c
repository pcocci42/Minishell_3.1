/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:52:09 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/* void	up_environ(char *current)
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
} */

/* void	up_envp(char *current, char **envp)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;

	i = 0;
	flag = 0;
	var = take_var(current);
	while (envp[i])
	{
		name = take_var(envp[i]);
		if (ft_strcmp(name, var) != 0)
		{	
			i++;
			free(name);
		}
		else
		{	
			printf("1\n");
			flag = 1;
			free(name);
			break ;
		}
	}
	free(var);
	envp[i] = malloc((sizeof(char)) * (ft_strlen(current) + 1));
	ft_strcpy(envp[i], current);
	if (flag == 0)
		envp[i + 1] = NULL;
}
 */

void	up_envp(char *current, char **envp, t_cmd *cmd)
{
	int		i;
	int		flag;
	char	*var;
	char	*name;
	(void)envp;

	i = 0;
	flag = 0;
	var = take_var(current); 

	while (cmd->cpy_env[i])
	{
		name = take_var(cmd->cpy_env[i]);
		if (ft_strcmp(name, var) != 0)
		{
			i++;
			free(name);
		}
		else
		{
			flag = 1;
			free(cmd->cpy_env[i]);
			free(name);
			break ;
		}
	}
	free(var);
	if (flag == 0)
		realloc_env(cmd, i);
	cmd->cpy_env[i] = malloc(sizeof(char) * (ft_strlen(current) + 1));
	ft_strcpy(cmd->cpy_env[i], current);
	if (flag == 0 && !var)
		cmd->cpy_env[i + 1] = NULL;
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
				up_envp(cmd->box[i][j], envp, cmd);
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
				up_envp(cmd->box[i][j], envp, cmd);
			}
			j++;
		}
		i++;
	}
}
