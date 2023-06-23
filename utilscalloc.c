/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilscalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:06:14 by lmasetti          #+#    #+#             */
/*   Updated: 2023/06/23 10:33:28 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*newarr;
	size_t	x;

	x = nmemb * size;
	if (nmemb != 0 && x / nmemb != size)
		return (NULL);
	newarr = (void *)malloc(x);
	if (!newarr)
		return (NULL);
	ft_bzero(newarr, x);
	return (newarr);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_in_out(t_cmd *cmd)
{
	if (cmd->input && ft_strcmp(cmd->input, "heredoc_tmp.txt") != 0)
		free(cmd->input);
	if (cmd->output)
		free(cmd->output);
}