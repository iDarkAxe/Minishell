/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:36:14 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/21 12:25:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_int(int *a, int *b);
void	ft_swap_char(char *a, char *b);
void	ft_swap_str(char **a, char **b);
void	ft_swap_mem(void **a, void **b);

/**
 * @brief Swap 2 int values
 *
 * @param a first value
 * @param b second value
 */
void	ft_swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Swap 2 char values
 *
 * @param a first value
 * @param b second value
 */
void	ft_swap_char(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Swap 2 string addresses
 *
 * @param a first value
 * @param b second value
 */
void	ft_swap_str(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Swap 2 memory adresses
 *
 * @param a first value
 * @param b second value
 */
void	ft_swap_mem(void **a, void **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
