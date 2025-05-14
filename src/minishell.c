/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:54:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/08 14:27:53 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "file.h"
#include "garbage.h"
#include "parsing.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static char	*read_stdin(void);

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
		ft_exit_int(0);
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
static char	*read_stdin(void)
{
	char	*prompt;
	char	*line;
	int		ret;

	while (1)
	{
		prompt = get_prompt_message();
		line = readline(prompt);
		if (ft_strncmp(prompt, DEFAULT_PROMPT, sizeof(DEFAULT_PROMPT)) != 0)
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
 * @brief Minishell that handles all the shell functions
 *
 * @param envp environmment
 * @return int
 */
int	minishell(char **envp)
{
	static int	ret = 0;
	t_command	*command;
	char		*line;
	char		*temp;
	char		**tokens;

	signal_init();
	read_context(envp);
	set_env(envp);
	line = NULL;
	while (1)
	{
		temp = read_stdin();
		tokens = parse_line(temp);
		command = tokeniser(tokens, envp);
		if (command->tokens->str == NULL || files_management(command) != 0)
		{
			free_command(command);
			free_array(tokens);
			continue ;
		}
		if (needs_to_be_forked(command) != 0)
			ret = prepare_command_forks(command, ret);
		else
			ret = prepare_command(command, ret);
		free_array(tokens);
		free_command(command);
	}
}
