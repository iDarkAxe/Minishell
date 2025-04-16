/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/14 14:25:25 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// READLINE
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
// OTHER
#include "env.h"
#include "garbage.h"
#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	print_env_vars(t_env_vars *env)
{
	t_var		*var;
	t_params	*param;

	if (!env)
		return ;
	var = env->head_var;
	while (var)
	{
		printf("%s=", var->value);
		param = var->head_params;
		while (param)
		{
			printf("%s", param->value);
			if (param->next)
				printf(":");
			param = param->next;
		}
		printf("\n");
		var = var->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_vars	*env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	print_env_vars(env);
	// for (int i = 0; envp[i] != NULL; i++)
	// 	printf("%s\n", envp[i]);
	(void)env;
	free_garbage();
	return (0);
}
