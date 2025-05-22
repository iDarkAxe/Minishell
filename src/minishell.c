/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/22 18:12:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/**
  ******************************************************************************
  * @file           : minishell.c
  * @brief          : Main program of the Minishell
  ******************************************************************************
  * @date 27 avril 2025
  * @mainpage Minishell
  * @section Introduction
  *
  * Make your own shell that performs worse than bash but it's yours.
  * 
  ******************************************************************************
*/
#include "builtins.h"
#include "env.h"
#include "file.h"
#include "garbage.h"
#include "minishell.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static char	*read_stdin(t_garbage *garbage);

/**
 * @brief Line condition to verify the return value of readline
 *
 * @param line line of readline
 * @return int 0, nothing checked, 1 is OK line, 2 is read another line
 */
static int	line_condition(char *line)
{
	if ((line != NULL && line[0] != '\0'))
		return (1);
	if (line == NULL)
		ft_exit_int_np(0);
	if (line[0] == '\0')
	{
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
static char	*read_stdin(t_garbage *garbage)
{
	char	*prompt;
	char	*line;
	int		ret;

	while (1)
	{
		prompt = get_prompt_message();
		line = readline(prompt);
		if (ft_strncmp(prompt, DEFAULT_PROMPT, sizeof(DEFAULT_PROMPT)) != 0)
			free_element_gb(garbage, prompt);
		ret = line_condition(line);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
	}
	add_to_garbage(garbage, line);
	add_history(line);
	return (line);
}

// FIXME réactiver read_context
/**
 * @brief Minishell that handles all the shell functions
 *
 * @param envp environmment
 * @return int
 */
int	minishell(char **envp)
{
	static int	ret = 0;
	t_data		data;
	char		*line;
	char		**tokens;

	signal_init();
	// read_context(&data.env, envp);
	set_env(&data.env, envp);
	while (1)
	{
		line = read_stdin(&data.garbage);
		tokens = parse_line(line);
		data.command = tokeniser(tokens, envp);
		if (data.command->tokens->str == NULL || files_management(data.command) != 0)
		{
			free_command(data.command);
			free_array(tokens);
			continue ;
		}
		if (needs_to_be_forked(data.command) != 0)
			ret = prepare_command_forks(&data, ret);
		else
			ret = prepare_command(&data, ret);
		free_array(tokens);
		free_command(data.command);
	}
}
