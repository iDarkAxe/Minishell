/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/30 11:14:14 by ppontet          ###   ########lyon.fr   */
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
char	*handle_expand(t_data *data, char *str);
char	*setup_string(t_data *data, char *str);

char	**expand_tildes_tokens(t_garbage *garbage, char **tokens);

//Utils
char	**ft_split_charset(const char *s, char *charset);
size_t	ft_strlen_charset(const char *str, const char *charset);
t_bool	is_dollar(char *str);
t_bool	detect_quote(const char *str);
size_t	ft_strlen_choose_c(const char *str, char c);
char	*fill_string(char *result, char *temp);
/** @} */
#endif
