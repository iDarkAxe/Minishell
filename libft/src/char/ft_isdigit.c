/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 11:37:18 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int character);

// could return 2048 or 0x100000000000 instead of 1
/**
 * @brief Check if arg is a digit
 *
 * @param character character to check
 * @return int 0 not digit, anything else is digit
 */
int	ft_isdigit(int character)
{
	if ((character >= '0' && character <= '9'))
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
// 	ft_putnbr_fd(isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = '9';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = 'e';
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// 	character = -97;
// 	ft_putnbr_fd(character, 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat attendu : ", 1);
// 	ft_putnbr_fd(isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putstr_fd("Resultat test   : ", 1);
// 	ft_putnbr_fd(ft_isdigit(character), 1);
// 	ft_putendl_fd("", 1);
// 	ft_putendl_fd("     -----     ", 1);
// }
