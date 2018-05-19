/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:38:33 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/19 20:00:44 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	lstfree(t_list *lst, t_list **main)
{
	t_list	*head;

	if (lst == *main)
	{
		*main = lst->next;
		free(lst);
		return ;
	}
	head = *main;
	while (head && head->next != lst)
	{
		head->next = lst->next;
		free(lst);
		head = head->next;
	}
}

void	print_string(t_list *start)
{
	size_t	i;
	size_t	len;
	t_list	*lst;
	char	*str;
	t_list	*tmp;

	lst = (t_list *)start->content;
	len = ft_lstlen(lst);
	str = ft_memalloc(len);
	i = 0;
	while (i < len)
	{
		tmp = lst;
		str[i] = *((char *)lst->content);
		free(lst->content);
		lst = lst->next;
		free(tmp);
		i++;
	}
	ft_printf("%s\n", str);
	ft_strdel(&str);
}

int		bit_shift(t_list *lst, int sig)
{
	lst->content_size--;
	if (sig == SIGUSR2)
		*((char *)(lst->content)) |= 1 << (lst->content_size);
	if (lst->content_size == 0 && *((char *)(lst->content)) == 0)
		return (1);
	return (0);
}

void	usr_handler(int sig, siginfo_t *sig_info, void *p)
{
	static t_list	*lst;
	t_list			*head;
	t_list			*start;

	if (p)
		;
	start = find_in_lst(&lst, (size_t)sig_info->si_pid);
	head = find_last_elem(start);
	if (bit_shift(head, sig))
	{
		print_string(start);
		lstfree(start, &lst);
	}
}

int		main(void)
{
	t_sigaction	sig_act;
	int			i;
	char		c;

	i = 8;
	c = 0;
	ft_printf("%d\n", getpid());
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = usr_handler;
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);
	while (1)
		pause();
}
