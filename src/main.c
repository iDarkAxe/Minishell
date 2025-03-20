/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/19 10:04:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// OTHER
#include <stdlib.h>
#include "minishell.h"

#include <unistd.h>

int	main(void)
{
	char	*str;

	str = readline("username@poste : ");
	signal_init();
	while (1)
	{
		if (str)
			printf("%s\n", str);
		usleep(100000);
	}
}
