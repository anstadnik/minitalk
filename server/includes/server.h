/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:35:04 by bcherkas          #+#    #+#             */
/*   Updated: 2018/05/20 17:35:25 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H

# include "../../libft/includes/libft.h"
# include "signal.h"

# define HASH_MAX_BYTES 32

typedef struct sigaction	t_sigaction;

typedef struct				s_data
{
	void					*content;
	ssize_t					content_size;
	int						counter;
	unsigned int			hash;
	struct s_data			*next;
}							t_data;

unsigned					check_hash(char *str, t_data *lst, size_t size);
t_data						*find_in_lst(t_data **lst, ssize_t pid);
t_data						*find_last_elem(t_data *daddy);
size_t						ft_lstlen(t_data *lst);

#endif
