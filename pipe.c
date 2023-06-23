/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/09 14:48:16 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	child_process(t_cmd *cmd, int i, int pipe_fds[i][2], char **envp)
{
	redirect_input(cmd, &cmd->exe, i, pipe_fds);
	redirect_output(cmd, &cmd->exe, i, pipe_fds);
	inter_exe(cmd, envp, i);
	if (i > 0)
		close(pipe_fds[i - 1][0]);
	if (i < cmd->exe.num_pipes)
		close(pipe_fds[i][1]);
}

void	parent_wait(int num_pipes, t_exe *exe, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i <= num_pipes)
	{
		waitpid(exe->pid, &cmd->exitstatus, 0);
		i++;
	}
}

void	set_in_out(int i, int pipe_fds[i][2], t_exe *exe)
{
	if (i > 0)
	{
		close(pipe_fds[i - 1][1]);
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][0]);
	}
	if (i < exe->num_pipes)
	{
		close(pipe_fds[i][0]);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][1]);
	}
}

void	exefine(int num_pipes, t_exe *exe, t_cmd *cmd)
{
	parent_wait(num_pipes, exe, cmd);
	dup2(exe->original_stdout, STDOUT_FILENO);
	close(exe->original_stdout);
}

void	execute_command(t_cmd *cmd, int num_pipes, char **envp)
{
	int		pipe_fds[100][2];
	int		i;

	set_struct(&cmd->exe, num_pipes);
	open_pipes(0, num_pipes, pipe_fds);
	i = 0;
	while (i <= num_pipes)
	{
		checking_redir(cmd, i);
		if (cmd->syntax_err == 1)
			return ;
		cmd->exe.pid = fork();
		error_fork(cmd->exe.pid);
		if (cmd->exe.pid == 0)
		{
			set_in_out(i, pipe_fds, &cmd->exe);
			child_process(cmd, i, pipe_fds, envp);
		}
		else
			close_pipes(i, pipe_fds);
		i++;
	}
	exefine(num_pipes, &cmd->exe, cmd);
}
