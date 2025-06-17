/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:23:43 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:40:45 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int character);

// could return 1024 or 0x10000000000 instead of 1
/**
 * @brief Check if arg is in ascii table
 *
 * @param character character to check
 * @return int 0 not in ascii table, anything else if in ascii table
 */
int	ft_isascii(int character)
{
	if ((character >= 0 && character <= 127))
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
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = '9';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = -2;
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = -97;
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isascii(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// }
