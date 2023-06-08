/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/08 18:32:41 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_nl(int tmp)
{
	if (tmp == 1)
		printf("\n");
}

void	ft_simple_echo(int n, t_cmd *cmd, char **parsed, int flag)
{
	cmd->tmp = n;
	if (check_echo(parsed, n) == 1)
		return ;
	while (parsed[n] != 0)
	{
		if (parsed[n][0] == '$' && parsed[n][1] != '?')
		{
			parsed[n]++;
			echo_dollar(parsed, n, flag, 0);
		}
		else if (parsed[n][0] == '\'' && parsed[n][1] == '$'
			&& ft_chr(parsed[n], '\'', 1) == 0)
		{
			parsed[n] += 1;
			echo_dollar(parsed, n, flag, 1);
		}
		else
			echo_no_dollar(parsed, n, flag);
		n++;
	}
	ft_nl(cmd->tmp);
	g_exitstatus = 0;
}

void	extra_echo(char **parsed, t_cmd *cmd)
{
	if (ft_strncmp(parsed[1], "$?", 2) == 0)
	{
		printf("%d\n", g_exitstatus);
		g_exitstatus = 0;
	}
	else
		ft_simple_echo(1, cmd, parsed, 0);
}

void	ft_echo(t_cmd *cmd, char **parsed)
{
	if (ft_strncmp(parsed[0], "echo", 4) == 0)
	{
		if (!parsed[1])
			printf("\n");
		else if (ft_strcmp(parsed[1], "$") == 0 && !parsed[2])
			printf("$\n");
		else if (ft_strncmp(parsed[1], "-n", 2) == 0)
		{
			if (ft_strncmp(parsed[2], "$?", 2) == 0)
			{
				printf("existatus %d\n", g_exitstatus);
				g_exitstatus = 0;
			}
			else
				ft_simple_echo(2, cmd, parsed, 0);
		}
		else
			extra_echo(parsed, cmd);
	}
}

void	custom_commands(t_cmd *cmd, char **parsed, char **envp)
{
	if (ft_strncmp(parsed[0], "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(parsed[0], "exit", 4) == 0)
		ft_exit(cmd);
	ft_echo(cmd, parsed);
	ft_export(cmd, parsed, envp);
	ft_env(cmd, parsed, envp);
	exit(0);
}
