/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:09:50 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:22:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stdlib.h>

typedef struct s_element	t_element;
typedef struct s_garbage	t_garbage;

/**
 * @brief Basic node for an element of a linked list
 *
 */
struct						s_element
{
	void					*ptr;
	void					*next;
};

/**
 * @brief Head of the linked list
 *
 */
struct						s_garbage
{
	size_t					n_elements;
	t_element				*head;
};

/**
 * @defgroup Garbage Garbage functions
 * @brief Functions to simulate a garbage
 * @{
 */
// Function to replace all the malloc by this to use the garbage
void						*malloc_gb(t_garbage *garbage, size_t size);
void						add_to_garbage(t_garbage *garbage, void *ptr);
void						free_element_gb(t_garbage *garbage, void *ptr);
char						*ft_strdup_gb(t_garbage *garbage,
								const char *source);
char						*ft_strndup_gb(t_garbage *garbage, const char *source, size_t len);

// Initialise the garbage and free it's content
void						garbage_init(t_garbage *garbage);
void						free_garbage(t_garbage *garbage);

// Private functions for garbage management
// t_garbage					*get_garbage(void);
void						print_garbage(t_garbage *garbage);

// Garbage stack management
t_element					*ft_garbagenew(void *ptr);
void						ft_garbageadd_front(t_garbage *garbage,
								t_element *new);
void						ft_garbageadd_back(t_garbage *stack,
								t_element *new) __attribute__((deprecated));
int							ft_garbageclear(t_garbage *data);
/** @} */
#endif
