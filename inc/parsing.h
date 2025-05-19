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
char	*parsing_minishell(const char *str);
char	**ft_split_charset(const char *s, char *charset);
char	*handle_expand(const char *str, size_t size);
void	handle_normal_characters(const char *str, char **string_to_stack, size_t size, size_t i);
char	*expand_variables_line(char *str);

//Utils
size_t	ft_strlen_charset(const char *str, const char *charset);
t_bool	is_dollar(char *str);

#endif
