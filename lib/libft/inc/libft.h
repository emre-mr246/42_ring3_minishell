/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:35 by emgul             #+#    #+#             */
/*   Updated: 2024/07/06 11:34:14 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_format
{
	char	specifier;
	int		specifier_index;
	int		printed_chars;
}	t_format;

// NUMBER
int			ft_atoi(const char *str);
char		*ft_itoa(int nbr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);

// LIST
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

// MEMORY
void		*ft_memchr(const void *ptr, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t count, size_t n);
void		ft_bzero(void *s, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

// STRING
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t		ft_strlcat(char *dst, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
size_t		ft_strlen(const char *s);
char		**ft_split(char *s, char c);
char		*ft_strchr(char *s, int c);
char		*ft_strdup(char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		*ft_strrchr(char *str, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);

// GET_NEXT_LINE
char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *left_str, char *buff);
char		*ft_strncpy_gnl(char *dest, char *src, unsigned int n);

// PRINTF
int			ft_printf(const char *input, ...);
int			ft_check_specifier(char *input);
int			ft_find_specifier_index(char *input);
int			ft_putchar(char c);
t_format	*ft_initialize_format(void);
void		ft_print_format(t_format *f, va_list args);
void		ft_putnbr(int n, t_format *f);
void		ft_putstr(char *str, t_format *f);
void		ft_putptr(unsigned long long ptr, t_format *f);
void		ft_puthex(unsigned int num, t_format *f);
void		ft_putunsigned(unsigned int nb, t_format *f);

#endif
