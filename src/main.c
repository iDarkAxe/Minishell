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

#include "env.h"
#include "garbage.h"
#include "minishell.h"
#include "parsing.h"
#include "pipex.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
// 	// t_env_vars	*copyy_env;
// 	t_env_vars	*env;
// 	// t_var		**head;
// 	// char		*str;
// 	char	**array;
//
// 	(void)argc;
// 	(void)argv;
// 	set_env(envp);
// 	env = get_env(envp);
//
// 	array = ft_split("TMUX", ' ');
// 	// copyy_env = copy_env(env);
// 	// printf("FIRST COPY\n\n");
// 	print_env_vars(env);
// 	// head = &copyy_env->head_var;
// 	// swap_vars(head, "PATH", "PWD");
// 	ft_unset(array);
// 	// swap_vars(head, "COLORTERM", "XMODIFIERS");
// 	// printf("\n\n");
// 	// printf("COPY AFTER SWAP\n\n");
// 	print_env_vars(env);
// 	// printf("\n\n");
// 	// printf("COPY AFTER SORT\n\n");
// 	// sort_ascii_order(copyy_env);
// 	// print_env_vars(copyy_env);
// 	// // for (int i = 0; envp[i] != NULL; i++)
// 	// 	printf("%s\n", envp[i]);
// 	// size_t	count = count_env(*env);
// 	// printf("%zu", count);
// 	// supp_var(head, "XMODIFIERS");
// 	// str = search_env(copyy_env, "ZSH");
// 	// ft_putstr_fd(str, 1);
// 	free_garbage();
// 	return (0);
// }
//
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (minishell(envp) != 0)
		ft_exit_int(1);
	free_garbage();
	return (0);
}
//
//
// int	main(int argc, char **argv, char **envp)
// {
// 	char		**array;
// 	char		*str;
// 	t_env_vars	*env;
//
// 	(void)argc;
// 	(void)argv;
// 	str = "export a";
// 	env = get_env(envp);
// 	// print_env_vars(env);
// 	array = ft_split(str, ' ');
// 	// for (int i = 0; array[i] != NULL; i++)
// 	// 	printf("%s\n", array[i]);
// 	// ft_export(array, env);
// 	ft_env(env);
// 	// print_env(env);
// 	printf("\n\n");
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_vars	*env;
// 	t_var		*var;
// 	(void)argc;
// 	(void)argv;
//
// 	set_env(envp);
// 	env = get_env();
// 	var = search_env_var(env, "PATH");
// 	printf ("%s", var->value);
// 	free_elements_params(var->head_params);
// 	if (var->head_params == NULL)
// 		return (0);
// 	printf("%s", var->head_params->value);
// 	print_env_vars(env);
// 	return (0);
// }

// TEST FREE_ENV
// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_vars	*env;
//
// 	(void)argc;
// 	(void)argv;
// 	set_env(envp);
// 	env = get_env();
// 	print_env_vars(env);
// 	free_env(env);
// 	return (0);
// }
// TEST CREATE_STR_WITH_PARAM

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_vars	*env;
//
// 	(void)argc;
// 	(void)argv;
// 	set_env(envp);
// 	env = get_env();
// 	print_env_vars(env);
//
// 	free_env(env);
// 	return (0);
// }
