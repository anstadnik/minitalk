/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:44:35 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/20 11:57:37 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t	ft_lstlen(t_data *lst)
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

t_data	*pid_lstnew(size_t pid)
{
	t_data	*lst;

	lst = (t_data *)malloc(sizeof(t_data));
	lst->content_size = pid;
	lst->content = NULL;
	lst->next = NULL;
	lst->hash = 0;
	lst->counter = 32;
	return (lst);
}

t_data	*new_son_lst(void)
{
	t_data	*lst;

	lst = (t_data *)malloc(sizeof(t_data));
	lst->next = NULL;
	lst->content = (char *)malloc(sizeof(char));
	*((char *)(lst->content)) = 0;
	lst->content_size = 8;
	return (lst);
}

t_data	*find_last_elem(t_data *daddy)
{
	t_data	*lst;

	if (daddy->content == NULL)
	{
		daddy->content = new_son_lst();
		return (daddy->content);
	}
	lst = (t_data *)daddy->content;
	while (lst->next && lst->content_size == 0)
		lst = lst->next;
	if (lst->content_size == 0)
	{
		lst->next = new_son_lst();
		lst = lst->next;
	}
	return (lst);
}

t_data	*find_in_lst(t_data **lst, ssize_t pid)
{
	t_data	*head;

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
