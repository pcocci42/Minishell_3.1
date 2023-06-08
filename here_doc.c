/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/07 10:58:20 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	read_heredoc(const char *delimiter, const char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open" );
		return ;
	}
	line = readline("> ");
	while (line != NULL)
	{
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		else
		{
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	close(fd);
}
