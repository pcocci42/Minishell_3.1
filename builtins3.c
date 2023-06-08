/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/08 18:40:46 by pcocci           ###   ########.fr       */
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
		printf("exit\n");
	free(cmd->cmd);
	free_altro(cmd);
	free(cmd);
	kill(0, SIGUSR1);
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
