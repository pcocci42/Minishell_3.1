/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/05/31 12:29:47 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	count_args(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	check_var(char *parsed)
{
	int i;

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

	int i;
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

char	*take_content(char *parsed)
{
	char *content;
	int i;
	int len;
	int	start;

	i = 0;
	len = 0;
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

void	handle_var(char **parsed, t_cmd *cmd)
{
	int i;
	t_var *copy;
	t_var *current;
	
	i = 0;
	cmd->var_count = 0;
	copy = cmd->variable;
    while (parsed[i]) {
        if (check_var(parsed[i]) == 1) {
            current = copy;
			cmd->var_count++;
            while (current) {
                if (ft_strcmp(take_var(parsed[i]), current->nome) == 0) {
                    current->content = take_content(parsed[i]);
                    break;
                }
                current = current->next;
            }
            if (!current) {
                // Variable not found, create a new one
                t_var *new_var = ft_lst(take_var(parsed[i]), take_content(parsed[i]));
                if (copy) {
                    while (copy->next) {
                        copy = copy->next;
                    }
                    copy->next = new_var;
                } else {
                    copy = new_var;
                }
            }
        }
        i++;
    }
    cmd->variable = copy; 
	//checks
	//ft_lstprint(cmd->variable);
	//i = ft_lstcount(cmd->variable);
	//printf("%d\n", i);
}