/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:35:04 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/19 19:58:34 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H

# include "../../libft/includes/libft.h"
# include "signal.h"
# include <unistd.h>

typedef struct sigaction	t_sigaction;

typedef struct				s_info
{
	int						counter;
	unsigned				hash;
}							t_info;

t_list						*find_in_lst(t_list **lst, size_t pid);
t_list						*find_last_elem(t_list *daddy);
size_t						ft_lstlen(t_list *lst);

#endif
