/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/04 14:32:59 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    ft_env(t_cmd *cmd, char **parsed, char **envp)
{
    int i;

    i = 0;
    if (ft_strcmp(parsed[0], "env") == 0  && (parsed[1] == NULL || cmd->f->re_out == 1))
    {
        print_envp2(envp);
        g_exitstatus = 0;
    }
    else if (ft_strcmp(parsed[0], "env") == 0  && parsed[1] != NULL)
        g_exitstatus = 130;
}

void	delete_content(char *str)
{	
	int i;
	char *tmp;
	i = 0;
	while (str[i] != '=')
		i++;
	tmp = malloc((sizeof(char)) * (i + 2));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = 0;
	//printf("%s\n", tmp);
	ft_strcpy(str, tmp);
}

void unset_enviroment(char* varname, char** envp) 
{
    int index = 0;
    int found = 0;

    while (envp[index] != NULL) 
	{
        if (strncmp(envp[index], varname, strlen(varname)) == 0 && envp[index][strlen(varname)] == '=') 
		{
            for (int i = index; envp[i] != NULL; i++) 
			{
                envp[i] = envp[i + 1];
            }
            found = 1;
            break;
        }
        index++;
    }
}

void	ft_unset(char **parsed, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (parsed[j])
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strcmp(parsed[j], take_var(envp[i])) == 0)
				unset_enviroment(parsed[j], envp);
			i++;
		}
		j++;
	}
	i = 0;
	j = 1;
	while (parsed[j])
	{
		i = 0;
		while (environ[i])
		{	
			if (ft_strcmp(parsed[j], take_var(environ[i])) == 0)
				unset_enviroment(parsed[j], environ);
			i++;
		}
		j++;
	}
}
