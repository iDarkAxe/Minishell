/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_pars_sing_fx1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:25:01 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/31 14:10:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "stdlib.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

void	no_changes_single(void)
{
	char	*str;

	str = "chaine \'mot\' joli";
	TEST_ASSERT_EQUAL_STRING(NULL, ft_remove_near_quotes(str, '\''));
}

void	changes_one_single_1(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "chai\'\'ne";
	expected = "chaine";
	new_str = ft_remove_near_quotes(str, '\'');
	testing_ft_remove_near_quotes(str, expected, new_str);
}

void	changes_one_single_2(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "chai\'ne mot joli \' ici \' \'    rw rrq w\'\' qew qw e \'\'";
	expected = "chai\'ne mot joli \' ici \' \'    rw rrq w qew qw e \'\'";
	new_str = ft_remove_near_quotes(str, '\'');
	testing_ft_remove_near_quotes(str, expected, new_str);
}

void	changes_one_single_3(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "chaine complexe \' \'\' \'\' \'\'\\ \'\'\' \'\' \'";
	expected = "chaine complexe \' \'\' \'\' \'\'\\ \' \'\' \'";
	new_str = ft_remove_near_quotes(str, '\'');
	testing_ft_remove_near_quotes(str, expected, new_str);
}

void	changes_one_single_4(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\' \'\' \'\'qwe \'\'\\ \'\'\'qwe \'\' \'";
	expected = "\' \'\'qwe \'\' \'\'\\ \'qwe \'\' \'";
	new_str = ft_remove_near_quotes(str, '\'');
	testing_ft_remove_near_quotes(str, expected, new_str);
}
