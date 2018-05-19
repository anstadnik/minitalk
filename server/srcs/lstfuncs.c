/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:44:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/19 19:38:25 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t	ft_lstlen(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list	*pid_lstnew(size_t pid)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	lst->content_size = pid;
	lst->content = NULL;
	lst->next = NULL;
	return (lst);
}

t_list	*new_son_lst(void)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	lst->next = NULL;
	lst->content = (char *)malloc(sizeof(char));
	*((char *)(lst->content)) = 0;
	lst->content_size = 8;
	return (lst);
}

t_list	*find_last_elem(t_list *daddy)
{
	t_list	*lst;

	if (daddy->content == NULL)
	{
		daddy->content = new_son_lst();
		return (daddy->content);
	}
	lst = (t_list *)daddy->content;
	while (lst->next && lst->content_size == 0)
		lst = lst->next;
	if (lst->content_size == 0)
	{
		lst->next = new_son_lst();
		lst = lst->next;
	}
	return (lst);
}

t_list	*find_in_lst(t_list **lst, size_t pid)
{
	t_list	*head;

	if (*lst == NULL)
	{
		*lst = pid_lstnew(pid);
		return (*lst);
	}
	head = *lst;
	while (head->next && head->content_size != pid)
		head = head->next;
	if (head->content_size == pid)
		return (head);
	head->next = pid_lstnew(pid);
	return (head->next);
}
