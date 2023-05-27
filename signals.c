/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:00:31 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/12 16:11:15 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_signal_ctrl_c(int sig)
{
	(void)sig;
	if (sig != 0)
		printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_ctrl_bs(int sig)
{
	if (sig == 12)
	{
		rl_redisplay();
	}
	return ;
}