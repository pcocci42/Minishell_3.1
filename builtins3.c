/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/23 18:43:41 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "unistd.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exitstatus = 0;
	}
	else
		g_exitstatus = 1;
}

void	ft_exit(t_cmd *cmd)
{	
	if (g_exitstatus != 139)
	{
		printf("exit\n");
		cmd->fine = 0;
		if (cmd->box[0][1])
			g_exitstatus = atoi(cmd->box[0][1]);
		if (cmd->cpy_env)
			free_envp(cmd);
		free(cmd->f);
		free_altro(cmd);
		ft_done(cmd);
	}
}

void	ft_cd(char **parsed)
{
	if (parsed[1])
	{
		if (chdir(parsed[1]) == -1)
			perror("chdir");
	}
	else
		chdir("/");
}
