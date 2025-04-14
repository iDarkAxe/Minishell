/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:55:10 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/26 16:20:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		exec(argc, argv, envp);
		i++;
	}
	return (0);
}
