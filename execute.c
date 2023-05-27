/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:17:38 by lmasetti          #+#    #+#             */
/*   Updated: 2023/05/24 18:20:13 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int check_exe(char **parsed)
{
    if ((parsed[0][0] == '.') && (parsed[0][1] == '/'))
    {
        return (1);
    }
    return (0);
}

void    exe_basic_cmd(char **parsed, char *command, char **envp) // function for basic bash command in /bin
{
    int len = ft_strlen(parsed[0]);
    
    ft_strlcpy(command, "/bin/", 9);
    ft_strlcat(command, parsed[0], 6 + len );
    //ft_printf("%s\n", command);
    if (!execve(command, parsed, envp))
    { 
        printf("error execve\n");
        return ;
    }
}

void    exe_cmd_usr(char **parsed, char *command, char **envp) // function for basic bash command in USR/bin
{
    int len = ft_strlen(parsed[0]);
    
    ft_strlcpy(command, "/usr/bin/", 10);
    ft_strlcat(command, parsed[0], 10 + len );
    //ft_printf("%s\n", command);
    if (!execve(command, parsed, envp))
    { 
        printf("error execve\n");
        return ;
    }
}

/*
PROBLEMA: EXECVE PRENDE UN ARRAY PER AVERE GLI ARGOMENTI, PROBABILMENTE VA CREATO QUA USANDO I E J COME INDICI
DI DOVE SI TROVA IL COMANDO E DOVE SI FERMANO GLI ARGOMENTI. DA VALUTARE IL DA FARSI.
*/

void    exeArgs(t_cmd *cmd, int j, int i)
{
    pid_t   pid;
    char    *envp[] = {"PATH=/bin", 0};
    char command[100];

    (void)j;
    (void)i;
    pid = fork();
    if (pid == -1) //fork check
    {
        printf("Failed fork... :(");
        return ;
    }
    if (pid != 0) //parent wait until child terminates
        waitpid(pid, &g_exitstatus, 0);
    else    // child runs the bash command
    {   
        {
            if (check_exe(cmd->parsed) == 0) //command in /bin/ 
                exe_basic_cmd(cmd->parsed, command, envp);
            else if (check_exe(cmd->parsed) != 0) //executable not a bash command
            {   
                execve(cmd->parsed[0], cmd->parsed, cmd->envp);
            }
        }
    }
}