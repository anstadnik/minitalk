/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 20:12:11 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/20 16:15:13 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

unsigned	check_hash(char *str, t_data *lst, size_t size)
{
	size_t			i;
	unsigned int	rez;

	i = 0;
	rez = 0;
	while (str[i])
		rez += (unsigned)(str[i++]);
	if (lst->hash == rez && str && *str)
	{
		write(1, str, size);
		write(1, "\n", 1);
		free(str);
		kill((pid_t)lst->content_size, SIGUSR2);
		return (1);
	}
	free(str);
	kill((pid_t)lst->content_size, SIGUSR1);
	return (0);
}
