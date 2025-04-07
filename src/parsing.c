/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:49:27 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/27 13:52:12 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "pipex.h"
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_env_var(char *envp[], char *user_var)
{
	size_t	size_user_var;
	int		i;

	i = 0;
	size_user_var = ft_strlen(user_var + 1);
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], user_var + 1, size_user_var) == 0)
		{
			if (ft_strlen(envp[i]) > size_user_var + 1)
				return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

t_bool	detect_pair_quote(char *str, char quote)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			i++;
			while (str[i])
			{
				if (str[i] == quote)
					return (TRUE);
				i++;
			}
			return (FALSE);
		}
		i++;
	}
	return (FALSE);
}

int	main(void)
{
	char	str[10] = "\'PATH\'";

	if (detect_pair_quote(str, '\'') ==  TRUE)
		printf("FIND");
	else
		printf("NOT FIND");

	return (0);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*prompt;
// 	char	*display;
// 	// char	*get_text;
// 	// size_t	size_env_var;
//
// 	if (argc < 1)
// 		return (1);
// 	(void)argv;
// 	(void)envp;
// 	// get_text = NULL;
// 	signal_init();
// 	display = get_prompt_message();
// 	if (!display)
// 		return (1);
// 	while (1)
// 	{
// 		prompt = readline(display);
// 		if (!prompt)
// 			return (1);
// 		if (detect_pair_quote(prompt, '\'') == TRUE)
// 			printf("find pair of single quote");
// 		else
// 			break ;
// 		// else
// 		// {
// 		// 	size_env_var = ft_strlen(prompt);
// 		// 	get_text = get_env_var(envp, prompt);
// 		// 	if (!get_text)
// 		// 		return (1);
// 		// 	ft_putstr_fd(get_text + size_env_var, 1);
// 		// 	ft_putstr_fd("\n", 1);
// 		// }
// 	}
// 	free(display);
// 	free(prompt);
// 	return (0);
// }
