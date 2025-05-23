/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/23 11:41:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stddef.h>

// from data_structure.h
typedef struct s_data		t_data;

// Functions about quotes
char	*ft_remove_near_quotes(char const *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
char	*parsing_minishell(t_data *data, const char *str);
char	**ft_split_charset(const char *s, char *charset);
char	*expand_variables_line(t_data *data, char *str);

//Utils
size_t	ft_strlen_charset(const char *str, const char *charset);
t_bool	is_dollar(char *str);

#endif
