/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_pars_doub_fx2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:25:06 by ppontet           #+#    #+#             */
/*   Updated: 2025/03/31 14:19:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"
#include "libft.h"
#include "stdlib.h"
#include "unity.h"
#include "unity_internals.h"
#include "tests.h"

void	changes_all_double(void)
{
	char	*str;
	char	*expected;
	char	*new_str;

	str = "\" \" \"\" \"errqet\" \"\" qweqwgq \"\" \" \"";
	expected = "\" \"  \"errqet\"  qweqwgq  \" \"";
	new_str = ft_remove_all_near_quotes(str, '\"');
	testing_ft_remove_near_quotes(str, expected, new_str);
	str = "huv\"we\"v\"\"qw\"ev\"\\\"\"\"vrw\"wvr\"\\\"v\"w""";
	expected = "huv\"we\"vqw\"ev\"\\\"vrw\"wvr\"\\\"v\"w""";
	new_str = ft_remove_all_near_quotes(str, '\"');
	testing_ft_remove_near_quotes(str, expected, new_str);
}
