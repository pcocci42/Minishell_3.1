/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/31 12:38:04 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//extern char **environ;

int ft_putenv(char *name, char *value, t_cmd *cmd)
{   
    int i;

    /* printf("%s\n", name);
    printf("%s\n", value); */
    i = 0;
    while (cmd->envp2[i])
        i++;
    cmd->envp2[i] = malloc(strlen(name) + strlen(value) + 2);
    ft_strcpy(cmd->envp2[i], name);
    strcat(cmd->envp2[i], "=");
    strcat(cmd->envp2[i], value);
    cmd->envp2[i + 1] = NULL;
    i = 0;
    while (cmd->envp[i])
        i++;
    cmd->envp[i] = malloc(strlen(name) + strlen(value) + 2);
    ft_strcpy(cmd->envp[i], name);
    strcat(cmd->envp[i], "=");
    strcat(cmd->envp[i], value);
    //printf("%s\n", cmd->envp[i]); 
    cmd->envp[i + 1] = NULL;
    g_exitstatus = 0;
    return (0);
}

int ft_putenv_ez(char *name, t_cmd *cmd)
{   
    int i;

    i = 0;

    while (cmd->envp[i])
        i++;
    cmd->envp[i] = malloc(strlen(name) + 1);
    strcpy(cmd->envp[i], name);
    cmd->envp[i + 1] = NULL; 
    //printf("nuovo elemento con putenv ez\n");
    g_exitstatus = 0;
    return (0);
}

int    check_environ(t_cmd *cmd, int j, char **parsed) // env
{   
    int i;

    i = 0;
    while (cmd->envp2[i])
    {
        if (ft_strcmp(take_var(parsed[j]), take_var(cmd->envp2[i])) == 0)
        {
            cmd->envp2[i] = malloc(strlen(take_var(parsed[j]))) + strlen(take_content(parsed[j]) + 2);
            strcpy(cmd->envp2[i], take_var(parsed[j]));
            strcat(cmd->envp2[i], "=");
            strcat(cmd->envp2[i], take_content(parsed[j]));
            return (1);
        }
        i++;
    }
    return (0);
}

int    check_environ2(t_cmd *cmd, int j, char **parsed) // export
{
    int i;

    i = 0;
    while (cmd->envp[i])
    {
        if (ft_strcmp(take_var(parsed[j]), take_var(cmd->envp[i])) == 0)
        {
            if(check_var(cmd->envp[i]) == 1)
            {  
                cmd->envp[i] = malloc(strlen(take_var(parsed[j]))) + strlen(take_content(parsed[j]) + 2);
                strcpy(cmd->envp[i], take_var(parsed[j]));
                strcat(cmd->envp[i], "=");
                strcat(cmd->envp[i], take_content(parsed[j]));
            }
            else
            {
                cmd->envp[i] = malloc(strlen(take_var(parsed[j]))) + strlen(take_content(parsed[j]) + 2);
                strcpy(cmd->envp[i], take_var(parsed[j]));
                strcat(cmd->envp[i], "=");
                strcat(cmd->envp[i], take_content(parsed[j]));
                i = 0;
                while (cmd->envp2[i])
                    i++;
                cmd->envp2[i] = malloc(strlen(parsed[j]) + 1);
                strcpy(cmd->envp2[i], parsed[j]);
                cmd->envp2[i + 1] = NULL;
            }
            return (1);
        }
        i++;
    }
    return (0);
}