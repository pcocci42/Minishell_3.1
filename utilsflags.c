/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:27:05 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/25 15:14:58 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	flag_init(t_flags *f)
{
	f->append_out = 0;
	f->d_quote = 0;
	f->pipe = 0;
	f->quote = 0;
	f->re_in = 0;
	f->re_out = 0;
	f->write_in = 0;
}