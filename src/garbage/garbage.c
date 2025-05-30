/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:27:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 11:24:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "garbage.h"
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Get the garbage object
 *
 * @return t_garbage* garbage access
 */
// t_garbage	*get_garbage(void)
// {
// 	static t_garbage	garbage;

// 	return (&garbage);
// }

/**
 * @brief Initialize the garbage and sets the values to 0
 *
 */
void	garbage_init(t_garbage	*garbage)
{
	ft_bzero(garbage, sizeof(garbage));
	garbage->head = NULL;
	garbage->n_elements = 0;
}

/**
 * @brief Add a pointer to the garbage list
 *
 * @param garbage garbage structure
 * @param ptr pointer to add
 */
void	add_to_garbage(t_garbage *garbage, void *ptr)
{
	void		*temp;

	temp = ft_garbagenew(ptr);
	if (temp == NULL)
	{
		free(ptr);
		free_garbage(garbage);
		ft_dprintf(2,
			"minishell: garbage: Critical error of malloc, exiting.\n");
		ft_exit_int_np(garbage, EXIT_FAILURE);
	}
	ft_garbageadd_front(garbage, temp);
	garbage->n_elements++;
}

/**
 * @brief Free the garbage
 *
 */
void	free_garbage(t_garbage *garbage)
{
	rl_clear_history();
	ft_garbageclear(garbage);
}

/**
 * @brief Replace the original malloc by storing the created adresses
 * into a garbage to remove them afterwards
 *
 * @param garbage garbage structure
 * @param size number of bytes to allocates
 * @return void*
 */
void	*malloc_gb(t_garbage *garbage, size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	add_to_garbage(garbage, ptr);
	return (ptr);
}
