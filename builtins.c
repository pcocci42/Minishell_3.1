/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/05/24 15:19:59 by lmasetti         ###   ########.fr       */
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

void	ft_simple_echo(int j, int n, t_cmd *cmd, int i)
{
	int	tmp;
	int	flag;
    (void)i;

	tmp = n;
	flag = 0;
	if (!cmd->parsed && n == 1)
    {
        g_exitstatus = 1;
        return ;
    }
	else
	{   
        if (cmd->parsed[j+n][0] == '$' && cmd->parsed[j+n][1] != '?')
        {
            cmd->parsed[j+n]++;
            while (cmd->parsed[j+n] != 0) //  e non si arriva al prossimo commando 
            {   
                /* printf("%s\n", cmd->parsed[j+n]); */
                if (ft_strncmp(cmd->parsed[j+n], "-n", 2) != 0 || flag == 1)
                {
                    printf("%s", ft_getenv(cmd, cmd->parsed[j+n]));
                    flag = 1;
                    if (cmd->parsed[j+ n + 1] != 0)
                        printf(" ");
                }
                n++;
            }
        }
        else
            while (cmd->parsed[j+n] != 0)
            {
                if (ft_strncmp(cmd->parsed[j+n], "-n", 2) != 0 || flag == 1)
                {
                    printf("%s", cmd->parsed[j+n]);
                    // flag = 1;
                    if (cmd->parsed[j+ n + 1] != 0)
                        printf(" ");
                }
                n++;
            }
	}
	if (tmp == 1)
		printf("\n");
    g_exitstatus = 0;
}

void    ft_echo(t_cmd *cmd, int j, int i)
{   
    if (ft_strncmp(cmd->parsed[j], "echo", 4) == 0)
    {
        
        if (ft_strncmp(cmd->parsed[j+1], "-n", 2) == 0)
        {
            if(ft_strncmp(cmd->parsed[j+2], "$?", 2) == 0)
            {
                printf("existatus %d\n", g_exitstatus);
                g_exitstatus = 0;
            }
            else
                ft_simple_echo(j, 2, cmd, i);
        }
        else
        {
            if(ft_strncmp(cmd->parsed[j+1], "$?", 2) == 0)
            {
                printf("exitstatus %d\n", g_exitstatus);
                g_exitstatus = 0;
            }
            else
                ft_simple_echo(j, 1, cmd, i);
        }
    }
}

void    custom_commands(t_cmd *cmd, int j, int i)  // hard coded commands;
{
    if (ft_strncmp(cmd->parsed[j], "exit", 6) == 0)
        ft_exit(cmd->parsed);
    if (ft_strncmp(cmd->parsed[j], "cd", 2) == 0)
        ft_cd(cmd->parsed, j);
    // if (ft_strncmp(cmd->parsed[j], "clear", 6) == 0)
    //     clear();
    if (ft_strncmp(cmd->parsed[j], "pwd", 3) == 0)
        ft_pwd();
    ft_echo(cmd, j, i);
    ft_export(cmd);
    ft_env(cmd, j);
    ft_unset(cmd, j);
    ft_prova_redirect(cmd, j);
    return;
}