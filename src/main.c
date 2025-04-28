/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/28 13:58:50 by lud-adam         ###   ########.fr       */
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
	t_env_vars	*copyy_env;
	t_var		**head;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	copyy_env = copy_env(env);
	printf("FIRST COPY\n\n");
	print_env_vars(copyy_env);
	head = &copyy_env->head_var;
	swap_vars(head, "PATH", "PWD");
	swap_vars(head, "COLORTERM", "XMODIFIERS");
	printf("\n\n");
	printf("COPY AFTER SWAP\n\n");
	print_env_vars(copyy_env);
	printf("\n\n");
	printf("COPY AFTER SORT\n\n");
	sort_ascii_order(copyy_env);
	print_env_vars(copyy_env);

	// // for (int i = 0; envp[i] != NULL; i++)
	// 	printf("%s\n", envp[i]);
	// size_t	count = count_env(*env);
	// printf("%zu", count);
	free_garbage();
	return (0);
}
