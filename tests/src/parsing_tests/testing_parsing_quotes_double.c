/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_parsing_quotes_double.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:33:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/31 14:26:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "stdlib.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

#define DEBUG 0

#ifndef DEBUG
# define DEBUG 0
#endif

// set stuff up here
void	set_up(void)
{
}

// clean stuff up here
void	tear_down(void)
{
	free_garbage();
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(no_changes_single);
	RUN_TEST(changes_one_single_1);
	RUN_TEST(changes_one_single_2);
	RUN_TEST(changes_one_single_3);
	RUN_TEST(changes_all_single);
	RUN_TEST(no_changes_double);
	RUN_TEST(changes_one_double_1);
	RUN_TEST(changes_one_double_2);
	RUN_TEST(changes_one_double_3);
	RUN_TEST(changes_all_double);
	return (UNITY_END());
}

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
