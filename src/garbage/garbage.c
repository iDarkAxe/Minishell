/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:27:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/16 10:28:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

/**
 * @brief Get the garbage object
 * 
 * @return t_garbage* garbage access
 */
t_garbage	*get_garbage(void)
{
	static t_garbage	garbage;

	return (&garbage);
}

/**
 * @brief Initialize the garbage and sets the values to 0
 * 
 */
void	garbage_init(void)
{
	t_garbage	*garbage;

	garbage = get_garbage();
	ft_bzero(garbage, sizeof(garbage));
}

/**
 * @brief Add a pointer to the garbage list
 * 
 * @param ptr pointer to add
 */
void	add_to_garbage(void *ptr)
{
	void		*temp;
	t_garbage	*garbage;

	garbage = get_garbage();
	temp = ft_garbagenew(ptr);
	if (temp == NULL)
	{
		free_garbage();
		print_fd(2, "Error of malloc, exiting.\n");
		exit(1);
	}
	ft_garbageadd_front(garbage, temp);
	garbage->n_elements++;
}

/**
 * @brief Free the garbage
 * 
 */
void	free_garbage(void)
{
	t_garbage	*garbage;

	garbage = get_garbage();
	ft_garbageclear(garbage);
}

/**
 * @brief Replace the original malloc by storing the created adresses 
 * into a garbage to remove them afterwards
 * 
 * @param size number of bytes to allocates
 * @return void* 
 */
void	*malloc_gb(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	add_to_garbage(ptr);
	return (ptr);
}
