/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/21 12:51:25 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_nl(int tmp)
{
	if (tmp == 1)
		printf("\n");
}

void	ft_simple_echo(int n, t_cmd *cmd, char **envp, int flag)
{
	cmd->tmp = n;
	cmd->f_echo = flag;
	if (check_echo(cmd->parsed, n, cmd) == 1)
		return ;
	while (cmd->parsed[n] != 0)
	{
		if (cmd->parsed[n][0] == '$' && cmd->parsed[n][1] != '?')
		{
			cmd->parsed[n]++;
			echo_dollar(envp, n, cmd, 0);
		}
		else if (cmd->parsed[n][0] == '\'' && cmd->parsed[n][1] == '$'
			&& ft_chr(cmd->parsed[n], '\'', 1) == 0)
		{
			cmd->parsed[n] += 1;
			echo_dollar(envp, n, cmd, 1);
		}
		else
			echo_no_dollar(cmd->parsed, n, flag);
		n++;
	}
	ft_nl(cmd->tmp);
	cmd->exitstatus = 0;
}

void	extra_echo(char **envp, t_cmd *cmd)
{
	if (ft_strncmp(cmd->parsed[1], "$?", 2) == 0)
	{
		printf("%d\n", cmd->exitstatus);
		cmd->exitstatus = 0;
	}
	else
		ft_simple_echo(1, cmd, envp, 0);
}

void	ft_echo(t_cmd *cmd, char **parsed, char **envp)
{	
	cmd->parsed = parsed;
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
				printf("existatus %d\n", cmd->exitstatus);
				cmd->exitstatus = 0;
			}
			else
				ft_simple_echo(2, cmd, envp, 0);
		}
		else
			extra_echo(envp, cmd);
	}
}

void	custom_commands(t_cmd *cmd, char **parsed, char **envp)
{
	if (ft_strncmp(parsed[0], "pwd", 3) == 0)
		ft_pwd(cmd);
	/* if (ft_strncmp(parsed[0], "exit", 4) == 0)
		ft_exit(cmd); */
	ft_echo(cmd, parsed, envp);
	ft_export(cmd, parsed, envp);
	ft_env(cmd, parsed, envp);
	exit(0);
}
