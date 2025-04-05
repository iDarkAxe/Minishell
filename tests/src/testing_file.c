/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:36:01 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/05 16:50:05 by ppontet          ###   ########lyon.fr   */
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
	RUN_TEST(testing_file_name);
	RUN_TEST(testing_file_perms_1);
	RUN_TEST(testing_file_perms_2);
	return (UNITY_END());
}
