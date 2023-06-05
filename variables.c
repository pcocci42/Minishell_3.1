/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:56:15 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/05 10:31:10 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void    ft_export(t_cmd *cmd, char **parsed, char **envp)
{   
    int i;
    
    i = 0;
    if (ft_strcmp(parsed[0], "export") == 0 && (parsed[1] == NULL || cmd->f->re_out == 1))
    {
        while (envp[i])
            printf("declare -x %s\n", envp[i++]);
    }
}
