/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/24 10:17:44 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//extern char **environ;

int    check_environ_ez(t_cmd *cmd, int j)
{   
    int i;

    i = 0;
    while (cmd->envp[i])
    {
        if (ft_strcmp(cmd->parsed[j], cmd->envp[i]) == 0)
        {
            printf("already present in export list");
            //g_exitstatus = 1;
            return (1);
        }
        i++;
    }
    return (0);
}

int     check_list(t_cmd *cmd, int i)
{
    t_var *tmp;

    tmp = cmd->variable;
    while(cmd->variable)
    {
        if(ft_strcmp(cmd->parsed[i], cmd->variable->nome) == 0)
        {
            ft_putenv(cmd->parsed[i], cmd->variable->content, cmd);
            cmd->variable = tmp;
            return(1);
        }
        cmd->variable = cmd->variable->next;
    }
    cmd->variable = tmp;
    return(0);
}

void    add_lst_ez(t_cmd *cmd, char *parsed)
{   
    t_var *tmp;
    t_var *new_var = ft_lst(parsed, NULL);
    tmp = cmd->variable;
    ft_lstadd_back(&cmd->variable, new_var);
    cmd->variable = tmp;
    //ft_lstprint(cmd->variable);
}

void    ft_export(t_cmd *cmd)
{   
    int i;

    i = 0;
    if (ft_strcmp(cmd->parsed[0], "export") == 0 && cmd->parsed[1] == NULL)
    {
        while (cmd->envp[i])
            printf("declare -x %s\n", cmd->envp[i++]);
    }
    else if (ft_strcmp(cmd->parsed[0], "export") == 0)
    {   
        i = 1;
        while (cmd->parsed[i])
        {   
            if (check_var(cmd->parsed[i]) == 1)
                export_full(cmd, i);
            else if (check_var(cmd->parsed[i]) == 0 && check_list(cmd,i) == 0) 
            {
                if(check_environ_ez(cmd,i) == 0)
                {
                    ft_putenv_ez(cmd->parsed[i], cmd);
                    add_lst_ez(cmd, cmd->parsed[i]);
                }
            }
            i++;
        }
    }       
}

void    export_full(t_cmd *cmd, int i)
{
    t_var *tmp;
    int q;
    int w;
    
    tmp = cmd->variable;
    while (cmd->variable)
        {
        if (ft_strcmp(take_var(cmd->parsed[i]), cmd->variable->nome) == 0)
        {
            q = check_environ2(cmd,i);
            w = check_environ(cmd,i);
            // printf("check su export = %d, check su env= %d\n", q,w);
            if(q == 0 && w == 0)
                {
                    ft_putenv(cmd->variable->nome, cmd->variable->content, cmd);
                    // printf("nuovo elemento con putenv\n");
                }
        }
        cmd->variable = cmd->variable->next;
        }
    cmd->variable = tmp;
}

