/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:12:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/11 11:21:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include "tests.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>

void	set_up(void)
{
}

// clean stuff up here
void	tear_down(void)
{
	tear_down_files();
	free_garbage();
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(parsing_tests);
	RUN_TEST(file_tests);
	RUN_TEST(lexer_simple);
	return (UNITY_END());
}
