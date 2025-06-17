/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:03:21 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 15:16:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int character);

// could return 1024 or 0x10000000000 instead of 1
/**
 * @brief Check if arg is a char or a digit (alphanumeric)
 *
 * @param character character to check
 * @return int 0 not char, anything else is char or digit
 */
int	ft_isalnum(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A'
			&& character <= 'Z') || (character >= '0' && character <= '9'))
		return (1);
	return (0);
}

// #include "libft.h"
// #include "unistd.h"
// #include <ctype.h>

// int main (void)
// {
// 	char character;

// 	character = 'c';
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = '9';
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = '\24';
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isalnum(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// }
