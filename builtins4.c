/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/20 13:19:25 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_putstr_quota(char *parsed)
{
	int		i;
	char	*var;

	var = malloc((sizeof(char)) * ft_strlen(parsed));
	i = 0;
	while (parsed[i] && parsed[i] != '\'')
	{
		if (parsed[i] == 18)
			parsed[i] = '|';
		var[i] = parsed[i];
		i++;
	}
	var[i] = 0;
	ft_strcpy(parsed, var);
	free(var);
	return (parsed);
}

void	echo_dollar(char **envp, int n, t_cmd *cmd, int squote)
{	
	char	*env;

	env = ft_getenv(cmd->parsed[n], envp);
	if (ft_strncmp(cmd->parsed[n], "-n", 2) != 0 || cmd->f_echo == 1)
	{
		if (squote == 0)
		{
			if (env != NULL)
				ft_putstr(env);
		}
		else
		{
			cmd->parsed[n] = ft_putstr_quota(cmd->parsed[n]);
			cmd->parsed[n]++;
			printf("\'%s\'", ft_getenv(cmd->parsed[n], envp));
	 
		}
		cmd->f_echo = 1;
		if (cmd->parsed[n + 1] != 0)
			printf(" ");
	}
	free(env);
}

void	ft_putstr(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == 20)
			parsed[i] = '$';
		if (parsed[i] == 18)
			parsed[i] = '|';
		write(1, &parsed[i], 1);
		i++;
	}
	write(1, " ", 1);
}

void	echo_no_dollar(char **parsed, int n, int flag)
{
	if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
	{
		ft_putstr(parsed[n]);
		flag = 1;
		if (parsed[n + 1] != 0)
			printf(" ");
	}
}

int	check_echo(char **parsed, int n, t_cmd *cmd)
{
	if (!parsed && n == 1)
	{	
		cmd->exitstatus = 1;
		return (1);
	}
	return (0);
}
