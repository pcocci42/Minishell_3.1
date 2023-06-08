/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/08 12:34:57 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_putstr_quota(char *parsed)
{
	int		i;
	char	*var;

	var = malloc((sizeof(char)) * ft_strlen(parsed));
	i = 0;
	while (parsed[i] && parsed[i] != '\'')
	{
		if (parsed[i] == 18)
			parsed[i] = '|';
		var[i] = parsed[i];
		i++;
	}
	var[i] = 0;
	ft_strcpy(parsed, var);
	free(var);
	return (parsed);
}

void	echo_dollar(char **parsed, int n, int flag, int squote)
{
	if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
	{
		if (squote == 0)
		{
			if (getenv(parsed[n]) != NULL)
				ft_putstr(getenv(parsed[n]));
		}
		else
		{
			parsed[n] = ft_putstr_quota(parsed[n]);
			parsed[n]++;
			printf("\'");
			printf("%s", getenv(parsed[n]));
			printf("\'");
		}
		flag = 1;
		if (parsed[n + 1] != 0)
			printf(" ");
	}
}

void	ft_putstr(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		if (parsed[i] == 20)
			parsed[i] = '$';
		if (parsed[i] == 18)
			parsed[i] = '|';
		write(1, &parsed[i], 1);
		i++;
	}
	write(1, " ", 1);
}

void	echo_no_dollar(char **parsed, int n, int flag)
{
	if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
	{
		ft_putstr(parsed[n]);
		flag = 1;
		if (parsed[n + 1] != 0)
			printf(" ");
	}
}

int	check_echo(char **parsed, int n)
{
	if (!parsed && n == 1)
	{	
		g_exitstatus = 1;
		return (1);
	}
	return (0);
}
