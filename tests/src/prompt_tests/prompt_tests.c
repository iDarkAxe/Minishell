/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lud-adam <lud-adam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:29:09 by lud-adam          #+#    #+#             */
/*   Updated: 2025/03/31 15:55:29 by lud-adam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

#define DEBUG 0

#ifndef DEBUG
# define DEBUG 0
#endif

// set stuff up here
void	set_up(void)
{
}

// clean stuff up here
void	tear_down(void)
{
	free_garbage();
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST();
	return (UNITY_END());
}
