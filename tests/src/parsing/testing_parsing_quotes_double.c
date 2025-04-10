/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_parsing_quotes_double.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:33:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/10 13:31:42 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "stdlib.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

void	parsing_tests(void)
{
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
	RUN_TEST(one_pair_simple);
	RUN_TEST(one_pair_double);
	RUN_TEST(quote_simple_not_closed);
	RUN_TEST(quote_double_not_closed);
	RUN_TEST(nested_single_quote_in_double);
	RUN_TEST(nested_double_quote_in_single);
	RUN_TEST(quote_with_intern_space);
	RUN_TEST(quote_closed_with_space_all_around_the_string);
	RUN_TEST(empty_string);
	RUN_TEST(only_spaces);
	RUN_TEST(simple_quote_with_a_double_quote_inside);
	RUN_TEST(double_quote_with_a_single_quote_inside);
	RUN_TEST(word_and_string_inside_double_quote);
}
