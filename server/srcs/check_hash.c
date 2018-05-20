/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 20:12:11 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/20 12:34:15 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

unsigned int reverseBits(unsigned int num)
{
    unsigned int  NO_OF_BITS = sizeof(num) * 8;
    unsigned int reverse_num = 0;
    unsigned int i;
    for (i = 0; i < NO_OF_BITS; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);  
   }
    return reverse_num;
}

unsigned	check_hash(char *str, t_data *lst)
{
	size_t			i;
	unsigned int	rez;

	i = 0;
	rez = 0;
	while (str[i])
		rez += (unsigned)(str[i++]);
//	lst->hash = reverseBits(lst->hash);
	ft_printf("SAVED HASH: %d, CALC HASH: %d\n", lst->hash, rez);
	if (lst->hash == rez)
	{
		ft_printf("%s\n", str);
		kill((pid_t)lst->content_size, SIGUSR2);
		return (1);
	}
	kill((pid_t)lst->content_size, SIGUSR1);
	return (0);
}
