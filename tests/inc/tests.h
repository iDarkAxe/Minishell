/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:21:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/17 10:17:26 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// FUNCTIONS TO TESTS
char	*ft_remove_near_quotes(const char *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);

// PRIVATE FUNCTION
void	testing_ft_remove_near_quotes(char *str, char *expected, char *new_str);

// Parsing pair empty of quotes
void	parsing_tests(void);
// Sub-tests
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

// Files
void	file_tests(void);
// Sub-tests
void	testing_file_name(void);
void	testing_file_perms_1(void);
void	testing_file_perms_2(void);
void	random_file_name_creation(void);
void	creating_heredoc(void);
void	creating_heredoc_ctrl_d(void);
// TearDown
void	tear_down_files(void);

// Built-ins
// ft_exit()
// void	ft_exit_tests(void);

// Lexer
void	lexer_simple(void);
