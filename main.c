/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:23 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/23 18:30:04 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int g_exitstatus;

void	take_input(t_cmd *cmd, char **envp)
{
	char	*tmp;

	cmd->shell_prompt = "@minishell:> \033[0;37m";
	tmp = ft_strjoin("\033[1;32m", getenv("LOGNAME"));
	cmd->shell_prompt = ft_strjoin(tmp, cmd->shell_prompt);
	free(tmp);
	cmd->cmd = readline(cmd->shell_prompt);
	if (cmd->cmd == NULL)
	{	
		if (cmd->cpy_env)
			free_envp(cmd);
		free(cmd->f);
		ft_done(cmd);
	}
	if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0)
	{	
		add_history(cmd->cmd);
		parse_input(cmd, envp);
	}
	else if (ft_strlen(cmd->cmd) == 0)
		return ;
	free(cmd->shell_prompt);
}

void	loop(t_cmd *cmd, char **envp)
{
	while (1)
	{
		take_input(cmd, envp);
		if (cmd->cmd != NULL && ft_strlen(cmd->cmd) != 0)	
			free_altro(cmd);
		if (cmd->fine == 0)
			break ;
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
	{	
		exit(0);
	}
	else
		return ;
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;

	(void) ac;
	(void) av;
	cmd = malloc(sizeof(t_cmd));
	cmd->f = malloc(sizeof(t_flags));
	cmd->index = malloc(sizeof(t_index));
	cmd->cpy_env = NULL;
	g_exitstatus = 0;
	cmd->fine = 1;
	copy_envp(cmd, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	cmd->count = 0;
	loop(cmd, envp);
	exit(g_exitstatus);
}
