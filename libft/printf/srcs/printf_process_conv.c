/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_process_conv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <astadnik@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:48:58 by astadnik          #+#    #+#             */
/*   Updated: 2018/03/15 14:13:04 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	printf_process_conv(t_list *head, t_printf_par *params)
{
	size_t	c;
	t_list	*first;

	first = head;
	c = 0;
	while (head)
	{
		if (!head->content_size)
		{
			if (((t_printf_flags *)head->content)->conv == 'n')
				printf_ptr(&first, head, params, &c);
			else if (((t_printf_flags *)head->content)->conv == 'm')
				printf_memory(head, params, &c);
			else if (ft_strchr("idDuUxXoOsScCpbkrq",
						((t_printf_flags *)head->content)->conv))
				printf_flags_hand(head, params, &c);
		}
		head = head->next;
	}
	return (1);
}
