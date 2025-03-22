/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/22 13:32:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdlib.h>

typedef struct s_element
{
	void		*ptr;
	void		*next;
}				t_element;

typedef struct s_garbage
{
	size_t		n_elements;
	t_element	*head;
}				t_garbage;

// Function to replace all the malloc by this to use the garbage
void			*malloc_gb(size_t size);
void			free_element_gb(void *ptr);
char			*ft_strjoins_gb(char **str);
char			*ft_strdup_gb(const char *source);
char			*ft_strndup_gb(const char *source, size_t len);

// Initialise the garbage and free it's content
void			garbage_init(void);
void			free_garbage(void);

// Private functions for garbage management
t_garbage		*get_garbage(void);
void			add_to_garbage(void *ptr);

// Garbage stack management
t_element		*ft_garbagenew(void *ptr);
void			ft_garbageadd_front(t_garbage *garbage, t_element *new);
void			ft_garbageadd_back(t_garbage *stack, t_element *new);
int				ft_garbageclear(t_garbage *data);

#endif
