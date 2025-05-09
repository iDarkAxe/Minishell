/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:21:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 15:36:00 by lud-adam         ###   ########.fr       */
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
void	no_changes(void);
void	one_pair_simple(void);
void	one_pair_double(void);
void	quote_simple_not_closed(void);
void	quote_double_not_closed(void);
void	nested_single_quote_in_double(void);
void	nested_double_quote_in_single(void);
void	quote_with_intern_space(void);
void	quote_closed_with_space_all_around_the_string(void);
void	empty_string(void);
void	only_spaces(void);
void	simple_quote_with_a_double_quote_inside(void);
void	double_quote_with_a_single_quote_inside(void);
void	word_and_string_inside_double_quote(void);
void	multiple_double_quote(void);
void	multiple_single_quote(void);

// Files
void	file_tests(void);
// Sub-tests
void	testing_file_name(void);
// void	testing_file_perms_1(void);
// void	testing_file_perms_2(void);
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
