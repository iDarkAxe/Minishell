/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:36:01 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 10:53:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include "tests.h"
#include "unity.h"
#include "unity_internals.h"
#include <fcntl.h>
#include <stdio.h>

void	testing_file_name(void)
{
	t_command	*command;
	char		*expected;
	char		*new_str;
	char		*line;
	char		**tokens;

	line = " <   fichier <  fichier2 cat   <feur  ";
	tokens = lexer(line);
	TEST_ASSERT_NOT_NULL(tokens);
	command = tokeniser(tokens, __environ);
	TEST_ASSERT_NOT_NULL(command);
	TEST_ASSERT_FALSE_MESSAGE(build_files_redirection(command),
		"Error in build_files_redirection");
	TEST_ASSERT_FALSE_MESSAGE(build_files_data(command),
		"Error in build_files_data");
	expected = "feur";
	new_str = command->file_in->name;
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
	expected = "fichier2";
	new_str = command->file_in->next->name;
	TEST_ASSERT_EQUAL_STRING(expected, new_str);
	free_garbage();
}

void	test_create_file(char *str, int perms)
{
	int	fd;

	if (access(str, F_OK) == 0)
	{
		unlink(str);
		fd = open(str, O_CREAT | O_RDONLY | O_WRONLY, perms);
		close(fd);
	}
	else
	{
		fd = open(str, O_CREAT | O_RDONLY | O_WRONLY, perms);
		close(fd);
	}
}

// Removed functions testing_file_perms_1 and testing_file_perms_2 
// as they were using an ancient style of struct of command

// void	testing_file_perms_1(void)
// {
// 	t_command	*command;

// 	command = malloc_gb(sizeof(t_command));
// 	if (command == NULL)
// 		return ;
// 	ft_bzero(command, sizeof(t_command));
// 	command->content = "cat <   fichier <  fichier2  <feur";
// 	if (build_files_redirection(command) != 0)
// 		return ;
// 	test_create_file("feur", 0666);
// 	build_files_data(command);
// 	TEST_ASSERT_EQUAL_INT(1, command->file_in->exist);
// 	TEST_ASSERT_EQUAL_INT(1, command->file_in->perm_read);
// 	TEST_ASSERT_EQUAL_INT(1, command->file_in->perm_write);
// 	if (access("feur", F_OK) == 0)
// 		unlink("feur");
// 	free_garbage();
// }

// void	testing_file_perms_2(void)
// {
// 	t_command	*command;

// 	command = malloc_gb(sizeof(t_command));
// 	if (command == NULL)
// 		return ;
// 	ft_bzero(command, sizeof(t_command));
// 	command->content = "cat <   fichier <  fichier2  <feur";
// 	if (build_files_redirection(command) != 0)
// 		return ;
// 	test_create_file("fichier2", 0222);
// 	build_files_data(command);
// 	TEST_ASSERT_EQUAL_INT(1, command->file_in->next->exist);
// 	TEST_ASSERT_EQUAL_INT(0, command->file_in->next->perm_read);
// 	TEST_ASSERT_EQUAL_INT(1, command->file_in->next->perm_write);
// 	if (access("fichier2", F_OK) == 0)
// 		unlink("fichier2");
// 	if (access("fichier", F_OK) == 0)
// 		unlink("fichier");
// 	TEST_ASSERT_EQUAL_INT(0, command->file_in->next->next->exist);
// 	TEST_ASSERT_EQUAL_INT(0, command->file_in->next->next->perm_read);
// 	TEST_ASSERT_EQUAL_INT(0, command->file_in->next->next->perm_write);
// 	free_garbage();
// }

void	tear_down_files(void)
{
	if (access("fichier", F_OK) == 0)
		unlink("fichier");
	if (access("feur", F_OK) == 0)
		unlink("feur");
	if (access("fichier2", F_OK) == 0)
		unlink("fichier2");
}
