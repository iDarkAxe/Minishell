/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:52:08 by lud-adam          #+#    #+#             */
/*   Updated: 2025/04/10 16:38:02 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <stddef.h>
# include "libft.h"

// Functions about quotes
char	*ft_remove_near_quotes(char const *str, const char character);
char	*ft_remove_all_near_quotes(const char *str, const char character);
char	*parsing_minishell(const char *str);

#endif
