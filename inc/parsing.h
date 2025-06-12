/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/11 14:30:52 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "garbage.h"
# include <stddef.h>

// from data_structure.h
typedef struct s_data		t_data;

/**
 * @defgroup Parsing Parsing functions
 * @brief Functions to parse the initial line
 * @{
 */
// Functions about quotes
char	*expand_str(t_data *data, char *str);
char	*setup_string(t_data *data, char *str);
char	*remove_quote(t_data *data, char *str, char *quote);
char	**expand_tildes_tokens(t_garbage *garbage, char **tokens);

//Utils
char	**ft_split_charset(const char *s, char *charset);
t_bool	is_dollar(char *str);
t_bool	detect_dollar_str(char *str);
t_bool	detect_quote(const char *str);
char	*fill_string(char *result, char *temp);

// Utils expand
char	*expand_or_trad_var(t_data *data, char *str, size_t size);
char	*search_env_str(t_data *data, const char *var, size_t size);
t_bool	is_expandable(char *s);
size_t	compute_size_expand_var(char *str);
size_t	compute_size(char *str);

// strlen
size_t	ft_strlen_charset(const char *str, const char *charset);
size_t	ft_strlen_ignore_first_c(const char *str, char c);
size_t	ft_strlen_choose_c(const char *str, char c);
size_t	ft_strlen_dollars(char *str);
size_t	ft_strlen_quotes_expand(char *str, char quote);
size_t	ft_strlen_quotes(char *str);

#endif
