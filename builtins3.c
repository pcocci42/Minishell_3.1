/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/21 14:08:47 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "unistd.h"

void	ft_pwd(t_cmd *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		cmd->exitstatus = 0;
	}
	else
		cmd->exitstatus = 1;
}

void	ft_exit(t_cmd *cmd)
{	
	if (cmd->exitstatus != 139)
	{
		printf("exit\n");
		g_fine = 0;
		free_altro(cmd);
		//free_box(cmd);
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
