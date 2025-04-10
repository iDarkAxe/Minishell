/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_parsing_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:23:16 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/09 12:02:13 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "parsing.h"
#include "libft.h"
#include "stdlib.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

char	*parsing_minishell(const char *str);

void	no_changes(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "simple";
	expected = "simple";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	one_pair_simple(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "'simple'";
	expected = "simple";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	one_pair_double(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"simple\"";
	expected = "simple";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	quote_simple_not_closed(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\'simple";
	expected = NULL;
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	quote_double_not_closed(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"simple";
	expected = NULL;
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	nested_single_quote_in_double(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"in \'the\' middle\"";
	expected = "in \'the\' middle";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	nested_double_quote_in_single(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\'in \"the\" middle\'";
	expected = "in \"the\" middle";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	quote_with_intern_space(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"   spaced string   \"";
	expected = "   spaced string   ";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	quote_closed_with_space_all_around_the_string(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"   spaced string   \"";
	expected = "   spaced string   ";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	empty_string(void)
{	
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"\"";
	expected = "";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	only_spaces(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"   \"";
	expected = "   ";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	simple_quote_with_a_double_quote_inside(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\'\"\'";
	expected = "\"";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	double_quote_with_a_single_quote_inside(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"\'\"";
	expected = "\'";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}

void	word_and_string_inside_double_quote(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\"word \"another word\"\"";
	expected = "word another word";
	new_str = parsing_minishell(str);
	add_to_garbage(new_str);
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
}
