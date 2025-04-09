/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_fx_printing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:13:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/07 15:15:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "garbage.h"
#include "libft.h"
#include "unity.h"
#include "unity_internals.h"

#define DEBUG 0

#ifndef DEBUG
# define DEBUG 0
#endif

void	testing_ft_remove_near_quotes(char *str, char *expected, char *new_str)
{
	if (DEBUG == 1)
		printf("\nstr len: %ld\n\t%s\nexp len: %ld\n\t%s\nres len: %ld\n\t%s\n",
			ft_strlen(str), str, ft_strlen(expected), expected,
			ft_strlen(new_str), new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
	if (new_str != NULL)
		free_element_gb(new_str);
}
