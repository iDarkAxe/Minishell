/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:10:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/30 11:47:02 by ppontet          ###   ########lyon.fr   */
/*   Updated: 2025/04/11 15:42:21 by lud-adam         ###   ########.fr       */
/*   Updated: 2025/04/29 10:26:50 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "garbage.h"
#include "garbage.h"
#include <readline/readline.h>
#include "parsing.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	char	*prompt;
//
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	signal_init();
// 	prompt = get_prompt_message();
// 	if (prompt == NULL)
// 	{
// 		free_garbage();
// 		write(2, "Error creating prompt\n", 22);
// 		exit(1);
// 	}
// 	str = readline(prompt);
// 	if (str == NULL)
// 		return (-1);
// 	add_history(str);
// 	add_to_garbage(str);
// 	free_garbage();
// }

char	*parsing_minishell(const char *str);


// {
// 	const char	*str;
// 	char		*result;
//
// 	// str = "simple"; // sans quote
// 	// str = "'simple'"; // quote simple bien fermée
// 	// str = "\"simple\""; // quote double bien fermée
// 	// str = "'simple"; // quote simple non fermée
// 	// str = "\"simple"; // quote double non fermée
// 	// str = "\"in 'the' middle\""; // quotes imbriquées
// 	// str = "'in \"the\" middle'"; // quotes imbriquées inversées
// 	// str = "\"   spaced string   \""; // quote avec espaces internes
// 	// str = "   \"trimmed\"   "; // quote bien fermée avec espaces autour
// 	// str = ""; // chaîne vide
// 	// str = "    "; // que des espaces
// 	// str = "'\"'"; // quote simple contenant une quote double
// 	// str = "\"'\""; // quote double contenant une quote simple
// 	str = "word \"another word\""; // mot + string entre quote
// 	// str = "wo\"r\"d";
// 	result = parsing_minishell(str);
// 	if (result)
// 	{
// 		printf("✅ [%s]\n", result);
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("❌ Parsing error or NULL result\n");
// 		printf("[%s]\n", result);
// 	}
// }

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

/**
 * @brief Main function
 * 
 * @param argc number of argument
 * @param argv array of arguments
 * @param envp environment
 * @return int 
 */
// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env_vars	*copyy_env;
// 	t_env_vars	*env;
// 	t_var		**head;
// 	// char		*str;
//
// 	(void)argc;
// 	(void)argv;
// 	env = get_env(envp);
// 	copyy_env = copy_env(env);
// 	printf("FIRST COPY\n\n");
// 	print_env_vars(copyy_env);
// 	head = &copyy_env->head_var;
// 	// swap_vars(head, "PATH", "PWD");
// 	// swap_vars(head, "COLORTERM", "XMODIFIERS");
// 	// printf("\n\n");
// 	// printf("COPY AFTER SWAP\n\n");
// 	// print_env_vars(copyy_env);
// 	// printf("\n\n");
// 	// printf("COPY AFTER SORT\n\n");
// 	// sort_ascii_order(copyy_env);
// 	// print_env_vars(copyy_env);
// 	// // for (int i = 0; envp[i] != NULL; i++)
// 	// 	printf("%s\n", envp[i]);
// 	// size_t	count = count_env(*env);
// 	// printf("%zu", count);
// 	supp_var(head, "XMODIFIERS");	
// 	// str = search_env(copyy_env, "ZSH");
// 	printf("\n\n");
// 	print_env_vars(copyy_env);
// 	// ft_putstr_fd(str, 1);
// 	free_garbage();
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (minishell(envp) != 0)
		ft_exit_int(1);
	free_garbage();
	return (0);
}
