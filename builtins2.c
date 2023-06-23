/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:36:59 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_env(t_cmd *cmd, char **parsed, char **envp)
{	
	(void)envp;

	if (ft_strcmp(parsed[0], "env") == 0 && (parsed[1] == NULL
			|| cmd->f->re_out == 1))
	{
		print_envp2(cmd->cpy_env);
		g_exitstatus = 0;
	}
	else if (ft_strcmp(parsed[0], "env") == 0 && parsed[1] != NULL)
		g_exitstatus = 130;
}

void	delete_content(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = malloc((sizeof(char)) * (i + 2));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = 0;
	ft_strcpy(str, tmp);
}

void	unset_enviroment(char	*varname, char	**envp)
{
	int	index;
	int	found;
	int	i;

	index = 0;
	found = 0;
	while (envp[index] != NULL)
	{
		if (strncmp(envp[index], varname, strlen(varname)) == 0
			&& envp[index][strlen(varname)] == '=')
		{	
			i = index;
			if (envp[i + 1] != NULL)
			{
				//envp[i] = envp[i + 1];
				ft_strcpy(envp[i], envp[i + 1]);
			}
			else
			{	
				free(envp[i]);
				envp[i] = NULL;
			}
			found = 1;
			break ;
		}
		index++;
	}
}

/* void	unset_environ(char **parsed, int i, int j)
{	
	char	*var;

	while (parsed[j])
	{
		i = 0;
		while (environ[i])
		{	
			var = take_var(environ[i]);
			if (ft_strcmp(parsed[j], var) == 0)
				unset_enviroment(parsed[j], environ);
			free(var);
			i++;
		}
		j++;
	}
} */

void	ft_unset(char **parsed, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*var;
	char	**envp;

	i = 0;
	j = 1;
	envp = cmd->cpy_env;
	while (parsed[j])
	{
		i = 0;
		while (envp[i])
		{	
			var = take_var(envp[i]);
			if (ft_strcmp(parsed[j], var) == 0)
			{	
				//unset_update(cmd, i);
				unset_enviroment(parsed[j], envp);
			}
			free(var);
			i++;
		}
		j++;
	}
	i = 0;
	j = 1;
	//unset_environ(parsed, i, j);
}
