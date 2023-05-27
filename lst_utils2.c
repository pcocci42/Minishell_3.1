/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:52:28 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/24 10:23:57 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_lstcount(t_var *lst)
{	
	int i;
	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_var **lst, t_var *new)
{
	t_var	*first_end;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	first_end = ft_lstlast(*lst);
	first_end->next = new;
}

