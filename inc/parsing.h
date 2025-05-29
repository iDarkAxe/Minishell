/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/28 10:18:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "garbage.h"
# include <stddef.h>

// from data_structure.h
typedef struct s_data		t_data;

// Functions about quotes
char	*ft_remove_near_quotes(char const *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
char	*clean_string(const char *str);
char	*parsing_minishell(t_data *data, const char *str);
char	**ft_split_charset(const char *s, char *charset);
char	*fill_string(char *result, char *temp);
char	*handle_expand(t_data *data, char *str);
char	*setup_string(t_data *data, char *str);
char	*expand_variables_line(t_data *data, char *str);
char	**expand_tildes_tokens(t_garbage *garbage, char **tokens);

//Utils
size_t	ft_strlen_charset(const char *str, const char *charset);
t_bool	is_dollar(char *str);
t_bool	detect_quote(const char *str);
char	*fill_string(char *result, char *temp);
size_t	ft_strlen_choose_c(const char *str, char c);

#endif
