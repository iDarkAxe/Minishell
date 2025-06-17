/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees_va.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:40 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 23:52:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

void	ft_frees_va(void *ptr, ...);

/**
 * @brief Frees multiple pointers using va_list
 * 
 * @param ptr first pointer
 */
void	ft_frees_va(void *ptr, ...)
{
	va_list	arg_ptr;
	void	*temp;

	va_start(arg_ptr, ptr);
	free(ptr);
	while (1)
	{
		temp = va_arg(arg_ptr, void *);
		if (temp == NULL)
			break ;
		free(temp);
	}
	va_end(arg_ptr);
}
