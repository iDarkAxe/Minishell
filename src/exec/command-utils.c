/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:08:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/30 10:35:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"
#include "ft_printf.h"

/**
 * @brief Print the command structure with it's tokens
 *
 * @param command command structure
 * @return ssize_t 0 or positive is OK, otherwise error
 */
ssize_t	print_command(t_command *command)
{
	t_token	*token;
	ssize_t	size;

	if (command == NULL)
		return (ft_dprintf(2, "No command to print\n"));
	size = 0;
	size += ft_printf("Command block at %p:\n", (void *)command);
	token = command->tokens;
	while (token)
	{
		size += ft_printf("  Token: %s\n", token->str);
		token = token->next;
	}
	return (size);
}

/**
 * @brief Print the commands structure with it's tokens
 *
 * @param command command structure
 * @return ssize_t 0 or positive is OK, otherwise error
 */
ssize_t	print_commands(t_command **command)
{
	t_command	*cmd;
	ssize_t		size;

	if (command == NULL)
		return (ft_dprintf(2, "No commands to print\n"));
	cmd = *command;
	size = 0;
	while (cmd && cmd->tokens)
	{
		size += print_command(cmd);
		cmd = cmd->next;
	}
	return (size);
}
