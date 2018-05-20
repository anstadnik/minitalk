/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:45:16 by astadnik          #+#    #+#             */
/*   Updated: 2018/05/20 13:38:42 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	g_bit;

void	handler(int sig)
{
	if (sig == 31)
		g_bit = 1;
	else if (sig == 30)
		g_bit = 0;
	else
		g_bit = -1;
}

int		send_letter(int pid, char c)
{
	char	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, c & 1 << i ? SIGUSR2 : SIGUSR1))
			return (1);
		if (DEBUG)
			ft_printf("%d", !!(c & 1 << i));
		usleep(20);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

int	send_hash(int pid, char *str)
{
	uint	hash;
	char	i;

	hash = 0;
	while (*str)
		hash += (uint)*str++;
	i = 32;
	while (i--)
	{
		if (kill(pid, hash & 1 << i ? SIGUSR2 : SIGUSR1))
			return (1);
		if (DEBUG)
			ft_printf("%d", !!(hash & 1 << i));
		usleep(20);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);

}

int		send_string(int pid, char *str)
{
	int	c;

	if (send_hash(pid, str))
		return (1);
	while (42)
	{
		if (send_letter(pid, *str))
			return (1);
		if (!*str++)
			break;
	}
	g_bit = -1;
	c = 0;
	while (c++ < 20)
	{
		usleep(20);
		if (g_bit == -1)
			kill(pid, SIGUSR1);
		else
			break ;
	}
	if (c == 20)
		return (1);
	return (g_bit ? 0 : -1);
}

int		main(int ac, char **av)
{
	int	pid;
	int	ret;

	if (ac != 3 || ft_isinteger(av[1]))
		return (1);
	if (DEBUG)
		ft_printf("%d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid = ft_atoi(av[1]);
	while ((ret = send_string(pid, av[2])) == -1)
		;
	return (ret);
}
