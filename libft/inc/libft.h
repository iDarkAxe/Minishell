/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:25:12 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/13 23:55:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>

/**
 * @brief Activate the variadic functions
 * 1 is activated, 0 is desactivated
 * 
 */
# ifndef FX_VA
#  define FX_VA 0
# endif

/**
 * @brief Basic type to mimic stdbool
 * 
 */
typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}			t_bool;

/**
 * @brief Structure for linked list
 */
typedef struct s_list
{
	void			*content;	/**< Pointer to the data stored in the node */
	struct s_list	*next;		/**< Pointer to the next node in the list */
}			t_list;

/**
 * @defgroup Basics Basic functions
 * @brief Basics functions 
 * @{
 */
int			ft_atoi(const char *nptr);
int			ft_atoi_base(char *str, char *base);
char		*ft_itoa(int n);
/** @} */

/**
 * @defgroup Char Char functions
 * @brief Char functions
 * @{
 */
int			ft_isalpha(int character);
int			ft_isdigit(int character);
int			ft_isalnum(int character);
int			ft_isascii(int character);
int			ft_isprint(int character);
int			ft_toupper(int character);
int			ft_tolower(int character);
int			ft_isspace(int character);
int			ft_iswhitespace(int character);
/** @} */

/**
 * @defgroup STR String functions
 * @brief String functions 
 * @{
 */
size_t		ft_strlen(const char *the_string);
size_t		ft_strlen_char(const char *the_string, int character);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *string, int searched_char);
char		*ft_strrchr(const char *string, int searched_char);
int			ft_strncmp(const char *first, const char *second, size_t length);
const char	*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *source);
char		*ft_strndup(const char *source, size_t len);
char		*ft_substr(char const *src, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoins(char **str);
# if (FX_VA == 1)

char		*ft_strjoins_va(char const *str, ...);
# endif

char		*ft_strtrim(char const *s, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
/** @} */

/**
 * @defgroup SORT Sorting arrays
 * @brief Sorting arrays
 * @{
 */
void		ft_rev_int(int *tab, size_t size);
/** @} */

/**
 * @defgroup Memory Memory functions
 * @brief Memory functions
 * @{
 */
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *destination, const void *source, size_t size);
void		*ft_memset(void *pointer, int value, size_t count);
void		*ft_memmove(void *destination, const void *source, size_t size);
const void	*ft_memchr(const void *memory_block, int searched_char,
				size_t size);
int			ft_memcmp(const void *src, const void *set, size_t size);
void		*ft_calloc(size_t element_count, size_t element_size);
/** @} */

/**
 * @defgroup Swap Swap functions
 * @brief Swap functions
 * @{
 */
void		ft_swap_int(int *a, int *b);
void		ft_swap_char(char *a, char *b);
void		ft_swap_str(char **a, char **b);
void		ft_swap_mem(void **a, void **b);
// SPECIAL SWAPS
void		ft_swap_int_no_temp(int *a, int *b);
void		ft_swap_char_no_temp(char *a, char *b);
// void		ft_swap_str_no_temp(char **a, char **b);
// void		ft_swap_mem_no_temp(void **a, void **b);
/** @} */

/**
 * @defgroup Print Print functions
 * @brief Print functions
 * @{
 */
ssize_t		ft_putchar_fd(const char c, int fd);
ssize_t		ft_putstr_fd(const char *s, int fd);
ssize_t		ft_putnstr_fd(const char *s, size_t len, int fd);
ssize_t		ft_putendl_fd(const char *s, int fd);
ssize_t		ft_putnendl_fd(const char *s, size_t len, int fd);
ssize_t		ft_putnbr_fd(long long n, int fd);

ssize_t		ft_putnbr_bin(int nbr);
// void		ft_putnbr_poneyvif(int nbr);
ssize_t		ft_putnbr_oct(int nbr);
ssize_t		ft_putnbr_hex(int nbr, char height);
ssize_t		ft_putnbr_hex_fd(unsigned int nbr, char height, int fd);
ssize_t		ft_putptr_fd(unsigned long nbr, int fd);
ssize_t		ft_putnbr_base(int nbr, const char *base);
size_t		ft_check_base_atoi(const char *base);
size_t		ft_check_base_putnbr(const char *base);
ssize_t		ft_putpointer_fd(const void *ptr);
/** @} */

/**
 * @defgroup LST Linked lists functions
 * @brief LST functions
 * @{
 */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_swap_nodes(t_list **start, t_list *lst1, t_list *lst2);
/** @} */

/**
 * @defgroup Free Free functions
 * @brief Free functions
 * @{
 */
void		ft_frees(void **ptr);
# if (FX_VA == 1)

void		ft_frees_va(void *ptr, ...);
# endif

/** @} */

#endif
