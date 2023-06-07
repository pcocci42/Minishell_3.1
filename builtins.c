/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/06/07 16:55:55 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    ft_putstr(char *parsed);

char    *ft_putstr_quota(char *parsed)
{   
    int i;
    char *var;

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

void    echo_dollar(char **parsed, int n, int flag, int squote)
{   
    if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
    {
        if (squote == 0)
        {
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

void    ft_putstr(char *parsed)
{   
    int i;

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
}

void    echo_no_dollar(char **parsed, int n, int flag)
{
    if (ft_strncmp(parsed[n], "-n", 2) != 0 || flag == 1)
    { 
        /* if (ft_strchr(parsed[n], 18))
            printf("|");
        if (ft_strchr(parsed[n], 20))
            printf("$"); 
        printf("%s", parsed[n]);  */
        ft_putstr(parsed[n]);
        flag = 1;
        if (parsed[n + 1] != 0)
            printf(" ");
    }
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
        while (parsed[n] != 0)
        {   
            if (parsed[n][0] == '$' && parsed[n][1] != '?')
            {   
                parsed[n]++;
                echo_dollar(parsed, n, flag, 0);
                n++;
            }
            else if (parsed[n][0] == '\'' && parsed[n][1] == '$' && ft_chr(parsed[n], '\'', 1) == 0)
            {
                parsed[n] += 1;
                echo_dollar(parsed, n, flag, 1);
                n++;
            }
            else
            {   
                echo_no_dollar(parsed, n, flag);
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
        else if (ft_strcmp(parsed[1], "$") == 0 && !parsed[2])
            printf("$\n");
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
    if (ft_strncmp(parsed[0], "pwd", 3) == 0)
        ft_pwd();
    if (ft_strncmp(parsed[0], "exit", 4) == 0)
        ft_exit();
    ft_echo(cmd, parsed);
    ft_export(cmd, parsed, envp);
    ft_env(cmd, parsed, envp);
    exit(0);
}