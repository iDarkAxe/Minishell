/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:32:13 by ppontet           #+#    #+#             */
/*   Updated: 2025/04/09 14:02:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	signal_handler(int sig, siginfo_t *info, void *context);
void		free_all(void);
int			signal_init(void);

/**
 * @brief Main function for initialising signals
 *
 * @return int 0 if the function ends correctly, -1 otherwise.
 */
int	signal_init(void)
{
	struct sigaction	action_receive;

	action_receive.sa_sigaction = signal_handler;
	sigemptyset(&action_receive.sa_mask);
	action_receive.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &action_receive, NULL);
	sigaction(SIGINT, &action_receive, NULL);
	return (0);
}

/**
 * @brief Signal handler
 * Ctrl+C = SIGINT -> print "^C" and displays a new prompt on a new line.
 * Ctrl+\ = SIGQUIT -> do nothing
 *
 * Search for now signals :
 * stty -a | grep -Ewoe '(intr|quit|susp|erase|kill|eof|eol|eol2) = [^;]+';
  stty -a | grep -Ewoe '(swtch|start|stop|susp) = [^;]+';
  stty -a | grep -Ewoe '(rprnt|werase|lnext|discard) = [^;]+';
 *
 * @param sig Signal received.
 * @param info Information about the signal.
 * @param context Context of the signal.
 */
static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGQUIT)
	{
		free_garbage();
		exit(1);
	}
	else if (sig == SIGINT)
		return ;
	else
	{
		free_garbage();
		exit(1);
	}
}
