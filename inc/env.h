/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:35 by lud-adam          #+#    #+#             */
/*   Updated: 2025/06/17 14:07:06 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "garbage.h"
# include "libft.h"
# include <stddef.h>

# define DEFAULT_PROMPT "Minishell$ "

# ifndef PROMPT_COLOR
#  define PROMPT_COLOR 1
# endif
# define COLOR_OFF "\033[0m"
# define CYAN_COLOR "\033[0;36m"
# define PURPLE_COLOR "\033[0;35m"

typedef struct s_var		t_var;
typedef struct s_env_vars	t_env_vars;
typedef struct s_params		t_params;
typedef struct s_vars		t_vars;
typedef struct s_supp		t_supp;

// from data_structure.h
typedef struct s_data		t_data;

struct						s_env_vars
{
	t_var					*head_var;
	size_t					count;
};

struct						s_var
{
	t_var					*next;
	char					*value;
	t_params				*head_params;
	size_t					count;
};

struct						s_params
{
	t_params				*next;
	char					*value;
};

struct						s_vars
{
	t_var					*prev_str;
	t_var					*prev_str_1;
	t_var					*curr_str;
	t_var					*curr_str_1;
	t_var					*curr;
	t_var					*curr_1;
	t_var					*temp;
};

struct						s_supp
{
	t_var					*curr;
	t_var					*prev_str;
};

// Utils
int							check_args_export(const char *str);
size_t						ft_strlen_choose_c(const char *str, char c);
int							ft_strcmp(const char *s1, const char *s2);
t_bool						detect_equal(char *str);
char						**build_elements(char *str);

// Utils env
t_env_vars					*copy_env(t_garbage *garbage, t_env_vars *env);
void						set_env(t_data *data, char *envp[]);
void						sort_ascii_order(t_garbage *garbage,
								t_env_vars *env);
t_var						*search_env_var(t_env_vars *env, char *var);
void						update_shlvl(t_garbage *garbage, t_env_vars *env);
void						update_last_token(t_data *data);
char						**env_to_array(t_data *data);

// Utils params
char						*create_str_with_params(t_garbage *garbage,
								t_params *params);
t_params					*get_param(t_garbage *garbage, char *content,
								size_t detect_equal);
t_params					*ft_paramlast(t_params *params);
void						ft_paramsadd_back(t_params **params, t_params *new);
void						print_export(t_env_vars *env);

// Utils vars
t_var						*ft_varlast(t_var *var);
t_var						*get_var(t_garbage *garbage, const char *var);
void						ft_varsadd_back(t_var **var, t_var *new);
void						ft_varsadd_front(t_var **head, t_var *new);
void						supp_var(t_garbage *garbage, t_var **head,
								char *str);
void						swap_vars(t_garbage *garbage, t_var **head,
								char *str, char *str2);

// free
void						free_params(t_garbage *garbage, t_params *element);
void						free_env(t_garbage *garbage, t_env_vars *env);

#endif
