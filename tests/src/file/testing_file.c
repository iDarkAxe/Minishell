/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:36:01 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 10:17:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "minishell.h"
#include "tests.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>

void	file_tests(void)
{
	RUN_TEST(testing_file_name);
	RUN_TEST(testing_file_perms_1);
	RUN_TEST(testing_file_perms_2);
	RUN_TEST(random_file_name_creation);
	RUN_TEST(creating_heredoc);
	RUN_TEST(creating_heredoc_ctrl_d);
}
