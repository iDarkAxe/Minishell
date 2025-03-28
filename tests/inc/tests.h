/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:21:59 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/28 16:22:01 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// FUNCTIONS TO TESTS
char	*ft_remove_near_quotes(const char *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
// PRIVATE FUNCTION
void	testing_ft_remove_near_quotes(char *str, char *expected, char *new_str);
// TESTS
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
