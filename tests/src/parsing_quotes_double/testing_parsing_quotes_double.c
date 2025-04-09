/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_parsing_quotes_double.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:33:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/07 15:18:23 by ppontet          ###   ########lyon.fr   */
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
}
