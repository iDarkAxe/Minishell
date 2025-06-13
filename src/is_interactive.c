/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_interactive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 15:15:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_interactive(void);

/**
 * @brief Function to read the context where this function is called
 * Verify if it's used in a tty or not.
 * To know, we check if stdin or stdout are attached to files or to the terminal
 * 
 * @return int 1 is interactive, 0 is not
 */
int	is_interactive(void)
{
	if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0
		&& isatty(STDERR_FILENO) != 0)
		return (1);
	return (0);
}
