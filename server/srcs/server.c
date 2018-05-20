/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:38:33 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/20 13:22:57 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	lstfree(t_data *lst, t_data **main)
{
	t_data	*head;

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

void	print_string(t_data *start)
{
	size_t	i;
	size_t	len;
	t_data	*lst;
	char	*str;
	t_data	*tmp;

	lst = (t_data *)start->content;
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
	check_hash(str, start);
}

int		bit_shift(t_data *lst, int sig)
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
	static t_data	*lst;
	t_data			*head;
	t_data			*start;

	if (p)
		;
	if ((size_t)sig_info->si_pid == 0)
		return ;
	start = find_in_lst(&lst, (size_t)sig_info->si_pid);
	if (--start->counter >= 0)
	{
		ft_printf("%d", sig == SIGUSR2 ? 1 : 0);
		if (sig == SIGUSR2)
			start->hash |= 1 << (start->counter);
		return ;
	}
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

	ft_printf("%d\n", getpid());
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = usr_handler;
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);
	while (1)
		pause();
}
