/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:16:03 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 13:15:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *first, const char *second, size_t length);

/**
 * @brief Find differences between first and second
 *
 * @param first first string to compare
 * @param second second string to compare
 * @param length number of characters to compare
 * @return int value of first - second
 */

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	index;

	index = 0;
	if (length == 0)
		return (0);
	while (index < (length - 1) && first[index] != '\0' && second[index] != '\0'
		&& first[index] == second[index])
		index++;
	return ((unsigned char)first[index] - (unsigned char)second[index]);
}
// #include <string.h>
// #include "libft.h"

// int main(void)
// {
//     char str[100] = "ABCDefGHIJKLM";
//     char str2[100] = "ABCDeFGHIJKLM";
//     int fd = 1;

//     ft_putstr_fd("Resultat attendu   : ", fd);
//     ft_putnbr_fd(strncmp(str, str2, 2), fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     ft_putnbr_fd(ft_strncmp(str, str2, 2), fd);
//     ft_putendl_fd("", fd);
//     ft_putendl_fd("     -----     ", fd);

//     ft_putstr_fd("Resultat attendu   : ", fd);
//     ft_putnbr_fd(strncmp(str, str2, 6), fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     ft_putnbr_fd(ft_strncmp(str, str2, 6), fd);
//     ft_putendl_fd("", fd);

//     ft_putendl_fd("     -----     ", fd);
//     ft_strlcpy(str, "abdEfghijkl", 5);
//     ft_strlcpy(str2, "abdffghijkl", 5);
//     ft_putstr_fd("Resultat attendu   : ", fd);
//     ft_putnbr_fd(strncmp(str, str2, ft_strlen(str)), fd);
//     ft_putendl_fd("", fd);
//     ft_putstr_fd("Resultat test   : ", fd);
//     ft_putnbr_fd(ft_strncmp(str, str2, ft_strlen(str)), fd);
//     ft_putendl_fd("", fd);
// }
