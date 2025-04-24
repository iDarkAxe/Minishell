/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:14:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/24 17:03:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include "unity.h"
#include "unity_internals.h"
#include <stdio.h>
#include <stdlib.h>

void	random_file_name_creation(void);
void	creating_heredoc(void);
void	creating_heredoc_ctrl_d(void);

void	random_file_name_creation(void)
{
	t_tmp	tmp;

	tmp = create_tmp(TMP_PATH, 12);
	if (tmp.fd == -1 || tmp.name == NULL)
	{
		if (tmp.name != NULL)
			free(tmp.name);
	}
	close(tmp.fd);
	unlink(tmp.name);
	TEST_ASSERT_NOT_EQUAL(-1, tmp.fd);
	TEST_ASSERT_NOT_NULL(tmp.name);
	free_element_gb(tmp.name);
}

void	creating_heredoc(void)
{
	t_command	*command;
	char		*line;
	char		**tokens;

	line = " <   fichier <<  koala cat   <fleur  ";
	tokens = lexer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	command = tokeniser(tokens, __environ);
	TEST_ASSERT_NOT_NULL(command);
	printf("Delimitor of heredoc is koala\n");
	TEST_ASSERT_FALSE_MESSAGE(build_files_redirection(command),
		"Error in build_files_redirection");
	TEST_ASSERT_FALSE_MESSAGE(build_files_data(command),
		"Error in build_files_data");
	free_garbage();
}

void	creating_heredoc_ctrl_d(void)
{
	t_command	*command;
	char		*line;
	char		**tokens;

	line = " <   fichier <<  koala cat   <fleur  ";
	tokens = lexer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	command = tokeniser(tokens, __environ);
	TEST_ASSERT_NOT_NULL(command);
	printf("Try Ctrl+D in heredoc (delimitor is koala in case)\n");
	TEST_ASSERT_FALSE_MESSAGE(build_files_redirection(command),
		"Error in build_files_redirection");
	TEST_ASSERT_FALSE_MESSAGE(build_files_data(command),
		"Error in build_files_data");
	free_garbage();
}
