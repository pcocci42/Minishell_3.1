/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:48:05 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/08 23:05:06 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_error(void)
{
	perror("open");
	exit(EXIT_FAILURE);
}

void	redirect_input(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2])
{
	if (cmd->f->write_in == 1 && cmd->hd_j == 0)
	{
		exe->input_fd = open("heredoc_tmp.txt", O_RDONLY);
		cmd->f->write_in = 1;
		if (exe->input_fd == -1)
			ft_error();
	}
	if (i == 0 && cmd->input != NULL)
	{
		exe->input_fd = open(cmd->input, O_RDWR, 0644);
		if (exe->input_fd == -1)
			ft_error();
	}
	else if (i > 0 && cmd->f->write_in == 0)
	{
		close(pipe_fds[i - 1][1]);
		exe->input_fd = pipe_fds[i - 1][0];
	}
	dup2(exe->input_fd, STDIN_FILENO);
	close(exe->input_fd);
}

void	redirect_output(t_cmd *cmd, t_exe *exe, int i, int pipe_fds[i][2])
{
	if (i == exe->last_command_index && cmd->output != NULL)
	{
		if (cmd->f->append_out)
			exe->output_fd = open(cmd->output, 01 | 0100 | 02000, 0644);
		else
			exe->output_fd = open(cmd->output, 01 | 0100 | 01000, 0644);
		if (exe->output_fd == -1)
		{	
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(exe->output_fd, STDOUT_FILENO);
		close(exe->output_fd);
	}
	else if (i == exe->last_command_index && cmd->output == NULL)
		exe->output_fd = exe->original_stdout;
	else if (i < exe->last_command_index)
	{
		close(pipe_fds[i][0]);
		exe->output_fd = pipe_fds[i][1];
	}
}

void	handle_here_doc_input(const char	*delimiter, t_cmd *cmd)
{
	int		input_fd;
	char	*line;

	input_fd = in_fd(cmd);
	if (input_fd == -1)
	{	
		perror("open");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	write_line(input_fd, line);
	while (line != NULL)
	{	
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line(input_fd, line);
	}
	close(input_fd);
}

void	set_struct(t_exe *exe, int num_pipes)
{
	exe->input_fd = STDIN_FILENO;
	exe->output_fd = STDOUT_FILENO;
	exe->original_stdout = dup(STDOUT_FILENO);
	exe->last_command_index = num_pipes;
	exe->num_pipes = num_pipes;
}
