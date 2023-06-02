/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/02 14:52:19 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"


char    *remove_tilde(char *str)
{
    int i = 0;
    int j = 1;
    char *new;
    int len = ft_strlen(str);
    new = malloc(sizeof(char) * len);
    while (str[i])
    {
        new[i] = str[j];
        i++;
        j++;
    }
    return(new);
}

char   *ft_getenv(t_cmd *cmd, char *to_print)
{
    t_var *tmp;
    char *value;

    tmp = cmd->variable;
    while (cmd->variable)
    {
        if (ft_strcmp(to_print, cmd->variable->nome) == 0)
            value = cmd->variable->content;
        cmd->variable = cmd->variable->next;
    }
    cmd->variable = tmp;
    return (value);
}

void	ft_simple_echo(int n, t_cmd *cmd, char **parsed)
{
	int	tmp;
	int	flag;
    (void)cmd;
	tmp = n;
	flag = 0;
	if (!parsed && n == 1)
    {
        g_exitstatus = 1;
        return ;
    }
	else
	{   
        if (parsed[n][0] == '$' && parsed[n][1] != '?')
        {
            parsed[n]++;
            while (parsed[n] != 0) //  e non si arriva al prossimo commando 
            {   
                /* printf("%s\n", cmd->parsed[j+n]); */
                if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
                {
                    if (ft_strchr(parsed[n], 18))
                        printf("|"); 
                    printf("%s", getenv(parsed[n]));
                    //perror("getenv");
                    flag = 1;
                    if (parsed[n + 1] != 0)
                        printf(" ");
                }
                n++;
            }
        }
        else
            while (parsed[n] != 0)
            {
                if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
                { 
                    if (ft_strchr(parsed[n], 18))
                        printf("|");
                    if (ft_strchr(parsed[n], 20))
                        printf("$"); 
                    printf("%s", parsed[n]);
                    // flag = 1;
                    if (parsed[n + 1] != 0)
                        printf(" ");
                }
                n++;
            }
	}
	if (tmp == 1)
		printf("\n");
    g_exitstatus = 0;
}

void    ft_echo(t_cmd *cmd, char **parsed)
{   
    if (ft_strncmp(parsed[0], "echo", 4) == 0)
    {
        if (!parsed[1])
            printf("\n");
        else if (ft_strncmp(parsed[1], "-n", 2) == 0)
        {
            if(ft_strncmp(parsed[2], "$?", 2) == 0)
            {
                printf("existatus %d\n", g_exitstatus);
                g_exitstatus = 0;
            }
            else
                ft_simple_echo(2, cmd, parsed);
        }
        else
        {
            if(ft_strncmp(parsed[1], "$?", 2) == 0)
            {
                printf("%d\n", g_exitstatus);
                g_exitstatus = 0;
            }
            else
                ft_simple_echo(1, cmd, parsed);
        }
    }
}

void    custom_commands(t_cmd *cmd, char **parsed, char **envp)  // hard coded commands;
{
    if (ft_strncmp(parsed[0], "exit", 6) == 0)
        ft_exit(cmd->parsed);
    if (ft_strncmp(parsed[0], "pwd", 3) == 0)
        ft_pwd();
    ft_echo(cmd, parsed);
    ft_export(cmd, parsed, envp);
    ft_env(cmd, parsed);
    exit(0);
}