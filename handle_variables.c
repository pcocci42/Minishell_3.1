/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/20 13:17:15 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_var(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*take_var(char *parsed)
{
	char	*var;
	int		i;

	i = 0;
	while (parsed[i] != '=' && parsed[i] != '\0')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (parsed[i] != '=' && parsed[i] != '\0')
	{
		var[i] = parsed[i];
		i++;
	}
	var[i++] = '\0';
	return (var);
}

char	*getcnt(char *parsed, int i, int len)
{
	char	*content;
	int		start;

	while (parsed[i] != '=')
		i++;
	i++;
	start = i;
	while (parsed[i] != '\0')
	{
		len++;
		i++;
	}
	i = 0;
	content = malloc(sizeof(char) * (len + 1));
	while (parsed[start] != '\0')
	{
		content[i] = parsed[start];
		i++;
		start++;
	}
	content[i] = '\0';
	return (content);
}

int	check_var_loop(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (check_var(parsed[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	print_envp2(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i++]);
	}
}
