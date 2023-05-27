/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasetti <lmasetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:52:28 by pcocci            #+#    #+#             */
/*   Updated: 2023/05/24 10:28:59 by lmasetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_lstiter(t_var *lst, char *nome, char *content)
{	
	int flag;

	flag = 0;
	if (!lst)
		return (2);
	while (lst)
	{
		if (ft_strcmp(lst->nome, nome) == 0)
		{
			lst->content = content;
			flag = 1;;
		}
		lst = lst->next;
	}
	return (flag);
}

void	ft_lstprint(t_var *lst)
{
	if (!lst)
		return;
	while (lst)
	{
		printf("%s\n", lst->nome);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

t_var	*ft_lst(char *nome, char *content)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->content = content;
    new->nome = nome;
	new->next = NULL;
	return (new);
}

t_var	*ft_lst_addcontent(t_var *lst, void *content, void *nome)
{   
	lst->content = content;
    lst->nome = nome;
	lst->next = NULL;
	return (lst);
}


t_var	*ft_lstlast(t_var *lst)
{	
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}