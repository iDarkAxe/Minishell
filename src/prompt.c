/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:58 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/18 17:25:18 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*prompt(char *prompt)
{
	char	*str;

	str = readline(prompt);
	return (str);
}

int	main(void)
{
	char	*test;

	test = prompt("");
	free(test);
	return (1);
}
