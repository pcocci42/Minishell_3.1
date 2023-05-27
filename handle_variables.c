/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:58:54 by paolococci        #+#    #+#             */
/*   Updated: 2023/05/18 15:54:05 by lmasetti         ###   ########.fr       */
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
	int	args;
	int i;
	int j;
	t_var *copy;

	j = 0;
	args = count_args(cmd->cmd, ' ');
	i = 0;
	//printf("arg count: %d\n", args);
	
	i = 0;
	while (args > 0)
	{
		if (check_var(parsed[i]) == 0)
			i++;
		args--;
	}
	args = count_args(cmd->cmd, ' ');
	while (parsed[j])
	{
		if (check_var(parsed[j]) == 1)
		{
			cmd->var_count++;
		}
		j++;
	}
	/* printf("primo parsed %s\n", cmd->parsed[i]);
	printf("index parsed %d\n", i);
	printf("var count: %d\n", cmd->var_count); */
	
	
	t_var *current;
	copy = cmd->variable;
    while (cmd->parsed[i]) {
        if (check_var(cmd->parsed[i]) == 1) {
            current = copy;
            while (current) {
                if (ft_strcmp(take_var(cmd->parsed[i]), current->nome) == 0) {
                    current->content = take_content(cmd->parsed[i]);
                    break;
                }
                current = current->next;
            }
            if (!current) {
                // Variable not found, create a new one
                t_var *new_var = ft_lst(take_var(cmd->parsed[i]), take_content(cmd->parsed[i]));
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
	i = ft_lstcount(cmd->variable);
	//printf("%d\n", i);
}