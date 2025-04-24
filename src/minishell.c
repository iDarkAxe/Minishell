/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/24 12:16:55 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int			search_command(t_command *command, char **tokens);
char		*read_stdin(void);
char		**parse_line(char *line);
int			minishell(char **envp);

static int	line_condition(char *line)
{
	if ((line != NULL && line[0] != '\0'))
		return (1);
	if (line == NULL || line[0] == '\0')
	{
		if (line != NULL)
			free(line);
		rl_on_new_line();
		return (2);
	}
	return (0);
}

/**
 * @brief Prototype for reading stdin
 *
 * @return char*
 */
char	*read_stdin(void)
{
	char	*prompt;
	char	*line;
	int		ret;

	while (1)
	{
		prompt = get_prompt_message();
		line = readline(prompt);
		if (ft_strncmp(prompt, DEFAULT_PROMPT, 12) != 0)
			free_element_gb(prompt);
		ret = line_condition(line);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
	}
	add_to_garbage(line);
	add_history(line);
	return (line);
}

/**
 * @brief Prototype for parsing
 *
 * @param line line to parse
 * @return char**
 */
char	**parse_line(char *line)
{
	char	**tokens;

	tokens = lexer(line);
	if (tokens == NULL)
		ft_exit((char *[]){"1", NULL});
	return (tokens);
}

// TODO Files management bloque pas l'exécution si un fichier n'existe pas
/* TODO Ouvrir les fichiers avec les modes appropriés
(READ, Write|Truncate, Append, et heredoc)
*/

/**
 * @brief Minishell prototype
 *
 * @param envp environmment
 * @return int
 */
int	minishell(char **envp)
{
	t_command	*command;
	char		*line;
	char		**tokens;

	signal_init();
	read_context(envp);
	while (1)
	{
		line = read_stdin();
		if (line == NULL)
			ft_exit((char *[]){"0", NULL});
		tokens = parse_line(line);
		command = tokeniser(tokens, envp);
		if (!command)
			ft_exit((char *[]){"1", NULL});
		if (files_management(command) != 0)
		{
			free_char_tokens(tokens);
			continue ;
		}
		if (search_command(command, tokens) != 0)
			ft_exit((char *[]){"1", NULL});
		free_char_tokens(tokens);
		free_command(command);
	}
}
