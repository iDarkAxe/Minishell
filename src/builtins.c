/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:55:10 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/20 16:57:22 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		i;

	i = 0;
	while (i < argc - 3)
	{
		exec(argc, argv, envp);
		i++;
	}
	return (0);
}
