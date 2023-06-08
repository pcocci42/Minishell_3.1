/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:23 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/09 00:12:24 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int			g_exitstatus;

extern char	**environ;

void	take_input(t_cmd *cmd, char **envp)
{
	char	*shell_prompt;
	char	*tmp;

	shell_prompt = "@minishell:> \033[0;37m";
	tmp = ft_strjoin("\033[1;32m", getenv("LOGNAME"));
	shell_prompt = ft_strjoin(tmp, shell_prompt);
	free(tmp);
	cmd->cmd = readline(shell_prompt);
	if (cmd->cmd == NULL)
	{	
		free(cmd->cmd);
		free(shell_prompt);
		free(cmd);
		exit(0);
	}
	if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0)
	{	
		add_history(cmd->cmd);
		parse_input(cmd, envp);
	}
	else if (ft_strlen(cmd->cmd) == 0)
		return ;
	free(shell_prompt);
}

void	loop(t_cmd *cmd, char **envp)
{
	while (1)
	{
		take_input(cmd, envp);
		if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0)
			free_altro(cmd);
	}
}

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig_num == SIGUSR1)
		exit(0);
	else
		return ;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;

	(void) ac;
	(void) av;
	cmd = malloc(sizeof(t_cmd));
	g_exitstatus = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	cmd->count = 0;
	loop(cmd, envp);
	free(cmd);
	exit(g_exitstatus);
}
