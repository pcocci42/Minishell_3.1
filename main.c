/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:25:23 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/25 15:16:32 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int g_exitstatus;

void    take_input(t_cmd *cmd)
{   
    char *shell_prompt;
    char *tmp;

    shell_prompt = "@minishell:> \033[0;37m";
	tmp = ft_strjoin("\033[1;32m", getenv("LOGNAME"));
	shell_prompt = ft_strjoin(tmp, shell_prompt);
    cmd->cmd = readline(shell_prompt);
    if (cmd->cmd == NULL)
    {   
        kill(0, SIGUSR1);
    }
    if (ft_strlen(cmd->cmd) != 0)
    {
        add_history(cmd->cmd);
        parse_input(cmd);
        process_input(cmd);
    }
}

void    loop(t_cmd *cmd)
{   
    
    struct sigaction action;
    action.sa_handler = handler;
    while(1)
    {   
        sigaction(SIGINT, &action, NULL);
        sigaction(SIGUSR1, &action, NULL);
        signal(SIGQUIT, SIG_IGN);
        take_input(cmd);
    }
}

void    handler(int sig_num)
{
    if (sig_num == SIGINT)
    {   
        printf("\n");
	    rl_replace_line("", 0);
	    rl_on_new_line();
	    rl_redisplay();
    }
    else if (sig_num == SIGUSR1)
    {   
        exit(g_exitstatus);
    }
    else
        return;
}

void   my_envp_init(t_cmd *cmd, char **envp)
{   
    int i;

    i = 0;
    cmd->envp = envp;
    while (envp[i])
    {
        i++;
    }
    cmd->envp2 = malloc(sizeof(char *) * i + 1);
    i = 0;
    while (envp[i])
    {
        cmd->envp2[i] = envp[i];
        i++;
    }
    cmd->variable = ft_lst("testa", "testa");
    cmd->f = malloc(sizeof(t_flags));
    flag_init(cmd->f);
    cmd->f->in = dup(STDIN_FILENO);
    cmd->f->out = dup(STDOUT_FILENO);
}

int main(int ac, char **av, char **envp)
{   
    (void)ac;
    (void)av;
    t_cmd *cmd;
    
    cmd = malloc(sizeof(t_cmd));
    clear();
    g_exitstatus = 0;
    my_envp_init(cmd, envp);
    loop(cmd);
    exit(g_exitstatus);
}