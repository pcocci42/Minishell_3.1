/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:27:36 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_path(char *full_path, char *dir, const char *string, char *path)
{
	while (dir != NULL)
	{
		full_path = (char *) malloc(ft_strlen(dir) + ft_strlen(string) + 2);
		if (full_path != NULL)
		{	
			dir = ft_strjoin(dir, "/");
			full_path = ft_strjoin(dir, string);
			if (access(full_path, X_OK) == 0)
			{
				free(path);
				free(full_path);
				return (0);
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	return (1);
}

int	is_valid_command(const char	*string, t_cmd *cmd)
{
	char	*path_env;
	char	*path;
	char	*dir;
	char	*full_path;

	full_path = NULL;
	if (ft_strchr(string, '=') != NULL)
		return (0);
	if (access(string, X_OK) == 0)
		return (0);
	path_env = ft_getenv("PATH", cmd);
	if (path_env != NULL)
	{
		path = ft_strdup(path_env);
		if (path != NULL)
		{	
			dir = strtok(path, ":");
			if (ft_path(full_path, dir, string, path) == 0)
				return (0);
			free(path);
		}
	}
	return (1);
}

void	ft_realloc(char **env)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	copy = malloc((sizeof(char *)) * (i + 1));
	j = i + 1;
	i = 0;
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[j] = NULL;
}

void	copy_envp(t_cmd *cmd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	cmd->cpy_env = malloc((sizeof(char *) * (i + 1)));
	i = 0;
	while (envp[i])
	{ 
		cmd->cpy_env[i] = malloc((sizeof(char)) * (ft_strlen(envp[i]) + 1));
		ft_strcpy(cmd->cpy_env[i], envp[i]);
		i++;
	}
	cmd->cpy_env[i] = NULL;
}

void	copy_envp2(t_cmd *cmd, char **envp, int j)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	cmd->cpy_env = malloc((sizeof(char *)) * (j + 1));
	i = 0;
	while (envp[i])
	{ 
		cmd->cpy_env[i] = malloc((sizeof(char)) * (ft_strlen(envp[i]) + 1));
		ft_strcpy(cmd->cpy_env[i], envp[i]);
		i++;
	}
	cmd->cpy_env[i] = NULL;
}