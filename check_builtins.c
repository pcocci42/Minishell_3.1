/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:34:16 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/23 16:54:07 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int check_cmds(char **parsed, int j)
{
    if (ft_strncmp(parsed[j], "exit", 4) == 0)
		return(0);
	else if (ft_strncmp(parsed[j], "cd", 2) == 0)
		return(0);
	else if (ft_strncmp(parsed[j], "export", 6) == 0)
		return(0);
    else if (ft_strncmp(parsed[j], "pwd", 3) == 0)
        return(0);
    else if (ft_strncmp(parsed[j], "echo", 4) == 0)
        return(0);
    else if (ft_strncmp(parsed[j], "unset", 5) == 0)
        return(0);
    else if (ft_strncmp(parsed[j], "env", 3) == 0)
        return(0);
    return (1);
}