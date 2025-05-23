/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:24:12 by lud-adam          #+#    #+#             */
/*   Updated: 2025/05/10 15:27:08 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stddef.h>

// Functions about quotes
char	*ft_remove_near_quotes(char const *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
char	*clean_string(const char *str);
char	*parsing_minishell(const char *str);
char	**ft_split_charset(const char *s, char *charset);
char	*fill_result(char *result, char *temp);
char	*handle_expand(char *str);

//Utils
size_t	ft_strlen_charset(const char *str, const char *charset);
t_bool	is_dollar(char *str);

#endif
