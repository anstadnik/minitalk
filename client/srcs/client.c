/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:45:16 by astadnik          #+#    #+#             */
/*   Updated: 2018/05/19 16:44:47 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	send_char(int pid, char chr)
{
	char	i;

	i = 8;
	while (i--)
	{
		if (!kill(pid, chr & 1 << i ? SIGUSR2 : SIGUSR1))
			return (1);
		if (DEBUG)
			ft_printf("%d", !!(chr & 1 << i));
		usleep(10);
	}
	if (DEBUG)
		ft_printf("\n");
	return (0);
}

int	send_string(int pid, char *str)
{
	while (42)
	{
		if (send_char(pid, *str))
			return (1);
		if (!*str++)
			return (0);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3 || ft_isinteger(av[1]))
		return (1);
	pid = ft_atoi(av[1]);
	return (send_string(pid, av[2]));
	//return (ac != 3 || ft_isinteger(av[1]) ? 1 : send_string(ft_atoi(av[1])), av[2]);
}
