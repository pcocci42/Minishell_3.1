/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:41:22 by paolococci        #+#    #+#             */
/*   Updated: 2023/05/31 12:46:54 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    ft_env(t_cmd *cmd, char **parsed)
{
    int i;

    i = 0;
    if (ft_strcmp(parsed[0], "env") == 0  && (parsed[1] == NULL || cmd->f->re_out == 1))
    {
        while (cmd->envp2[i])
            printf("%s\n", cmd->envp2[i++]);
        g_exitstatus = 0;
    }
    else if (ft_strcmp(parsed[0], "env") == 0  && cmd->parsed[1] != NULL)
        g_exitstatus = 130;
}

void    ft_unset_envp1(t_cmd *cmd, int x)
{
	char	**new_env;
	int		i;
	int		j;
	int		sp;

	i = -1;
	j = 0;
	if (!cmd->parsed[x])
		return ;
	while (cmd->envp[++i])
		if (ft_strcmp(take_var(cmd->envp[i]), cmd->parsed[x]) == 0)
			break ;
	sp = i;
	if (!cmd->envp[i])
		return ;
	while (cmd->envp[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	i = -1;
	while (cmd->envp[++i])
		if (i != sp)
			new_env[j++] = cmd->envp[i];
	cmd->envp = new_env;
}

void    ft_unset_envp2(t_cmd *cmd, int x)
{
	char	**new_env;
	int		i;
	int		j;
	int		sp;

	i = -1;
	j = 0;
	if (!cmd->parsed[x])
		return ;
	while (cmd->envp2[++i])
		if (ft_strcmp(take_var(cmd->envp2[i]), cmd->parsed[x]) == 0)
			break ;
	sp = i;
	if (!cmd->envp2[i])
		return ;
	while (cmd->envp2[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	i = -1;
	while (cmd->envp2[++i])
		if (i != sp)
			new_env[j++] = cmd->envp2[i];
	cmd->envp2 = new_env;
}

/* void    ft_unset(t_cmd *cmd, char **parsed)
{
    int i;

    i = 1;
    while (ft_strncmp(parsed[0], "unset", 5) == 0 && parsed[i])
    {
        ft_unset_envp1(cmd,i);
        ft_unset_envp2(cmd,i);
        i++;
    }
} */

// void    ft_prova_redirect(t_cmd *cmd)
// {
// 	if (ft_strncmp(cmd->parsed[j], "<<", 2) == 0)
//     {
//        handle_input_heredoc(cmd->parsed[j+1]);
//     }
//     else if (ft_strncmp(cmd->parsed[j], ">>", 2) == 0)
//     {
//        handle_output_append_redirection(cmd->parsed[j+1]);
//     }
//     else if (ft_strncmp(cmd->parsed[j], "<", 1) == 0)
//     {
//        handle_input_redirection(cmd->parsed[j+1]);
//     }
//     else if (ft_strncmp(cmd->parsed[j], ">", 1) == 0)
//     {
//        handle_output_redirection(cmd->parsed[j+1]);
//     }
//     else if (ft_strncmp(cmd->parsed[j], "|", 1) == 0)
//     {
//     //    pipala;
//     }
//     else
//         return;
// }