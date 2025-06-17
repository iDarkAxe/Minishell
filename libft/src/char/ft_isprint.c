/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:32:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 15:16:57 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int character);

// could return 16384 or 0x10000000000000 instead of 1
/**
 * @brief Check if arg is in ascii table and printable
 *
 * @param character character to check
 * @return int 0 not in ascii table, anything else if in ascii table
 */
int	ft_isprint(int character)
{
	if ((character >= 32 && character <= 126))
		return (1);
	return (0);
}
// #include "libft.h"
// #include "unistd.h"
// #include <ctype.h>

// int main (void)
// {
// 	char character;

// 	character = '1';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = '9';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = 'e';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = -97;
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isprint(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// }
