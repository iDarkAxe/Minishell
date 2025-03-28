/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_parsing_quotes_double.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:33:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/28 17:00:45 by ppontet          ###   ########lyon.fr   */
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

// FUNCTIONS TO TESTS
char	*ft_remove_near_quotes(const char *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
// PRIVATE FUNCTION
void	testing_ft_remove_near_quotes(char *str, char *expected, char *new_str);
// TESTS
void	no_changes_single(void);
void	changes_one_single_1(void);
void	changes_one_single_2(void);
void	changes_one_single_3(void);
void	changes_one_single_4(void);
void	changes_all_single(void);
void	no_changes_double(void);
void	changes_one_double_1(void);
void	changes_one_double_2(void);
void	changes_one_double_3(void);
void	changes_one_double_4(void);
void	changes_all_double(void);

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
	RUN_TEST(no_changes_double);
	RUN_TEST(changes_one_double_1);
	RUN_TEST(changes_one_double_2);
	RUN_TEST(changes_one_double_3);
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
