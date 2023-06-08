/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:23:42 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/07 10:58:39 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_input_redirection(char	*filename)
{
	int	file;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDIN_FILENO);
	close(file);
}

void	handle_output_redirection(char	*filename)
{
	int	file;

	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}

void	handle_input_heredoc(char	*delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	read = getline(&line, &len, stdin);
	while (read != -1)
	{
		if (strcmp(line, delimiter) == 0)
			break ;
	}
	free(line);
}

void	handle_output_append_redirection(char	*filename)
{
	int	file;

	file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
}
