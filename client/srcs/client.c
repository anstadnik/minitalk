/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:45:16 by astadnik          #+#    #+#             */
/*   Updated: 2018/05/20 17:34:31 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	g_bit;

void	handler(int sig)
{
	if (sig == SIGUSR2)
		g_bit = 1;
	else if (sig == SIGUSR1)
		g_bit = 0;
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
		usleep(50);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

int		send_hash(int pid, char *str)
{
	t_uint	hash;
	char	i;

	hash = 0;
	while (*str)
		hash += (t_uint)*str++;
	i = 32;
	while (i--)
	{
		if (kill(pid, hash & 1 << i ? SIGUSR2 : SIGUSR1))
			return (1);
		if (DEBUG)
			ft_printf("%d", !!(hash & 1 << i));
		usleep(50);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

int		send_string(int pid, char *str)
{
	int	c;

	g_bit = -1;
	if (send_hash(pid, str))
		return (1);
	while (42)
	{
		if (send_letter(pid, *str))
			return (1);
		if (!*str++)
			break ;
	}
	c = 0;
	while (c++ < 50)
	{
		usleep(100);
		if (g_bit == -1)
			kill(pid, SIGUSR1);
		else
			return (g_bit ? 0 : -1);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int	pid;
	int	ret;

	if (ac != 3 || ft_isinteger(av[1]) || !ft_strlen(av[2]))
	{
		ft_printf("{red}Wrong parameters\n{eoc}");
		return (1);
	}
	if (DEBUG)
		ft_printf("%d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid = ft_atoi(av[1]);
	while ((ret = send_string(pid, av[2])) == -1)
		;
	if (ret == 0 && !ft_strcmp(av[2], "ping"))
		ft_printf("{green}pong\n{eoc}");
	return (ret);
}
