/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:45:16 by astadnik          #+#    #+#             */
/*   Updated: 2018/05/19 21:29:03 by astadnik         ###   ########.fr       */
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

int		send(int pid, void *data, size_t size)
{
	char	*ptr;

	ptr = (char *)data;
	while (size--)
	{
		if (kill(pid, *ptr & 1 << size % 8 ? SIGUSR2 : SIGUSR1))
			return (1);
		if (DEBUG)
			ft_printf("%d", !!(*ptr & 1 << size % 8));
		if (!(size % 8))
			ptr++;
		usleep(20);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

uint	get_hash(char *str)
{
	uint	rez;

	rez = 0;
	while (*str)
		rez += (uint)*str++;
	return (rez);
}

int		send_string(int pid, char *str)
{
	uint	hash;

	hash = get_hash(str);
	if (send(pid, &hash, sizeof(int) * 8))
		return (1);
	while (42)
	{
		if (send(pid, str, sizeof(char) * 8))
			return (1);
		if (!*str++)
			break;
	}
	g_bit = -1;
	while (42)
	{
		usleep(20);
		if (g_bit == -1)
			kill(pid, SIGUSR1);
		else
			break ;
	}
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
