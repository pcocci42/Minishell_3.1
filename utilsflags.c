/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paolococci <paolococci@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:27:05 by pcocci            #+#    #+#             */
/*   Updated: 2023/06/02 15:21:52 by paolococci       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	flag_init(t_cmd *cmd)
{
	cmd->f->append_out = 0;
	cmd->f->d_quote = 0;
	cmd->f->pipe = 0;
	cmd->f->quote = 0;
	cmd->f->re_in = 0;
	cmd->f->re_out = 0;
	cmd->f->write_in = 0;
	cmd->syntax_err = 0;
}