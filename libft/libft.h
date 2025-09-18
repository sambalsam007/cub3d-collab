/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:12:30 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/10 18:10:20 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ============================================================================
** Standard Library Headers
** ========================================================================= */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <sys/wait.h>

/* ============================================================================
** Project-Specific Headers
** ========================================================================= */
# include "src/printf/ft_printf.h"

/* ============================================================================
** Definitions
** ========================================================================= */
# define BUFFER_SIZE 1

/* ============================================================================
** Structures
** ========================================================================= */
typedef struct s_list
{
	long			content;
	int				index;
	struct s_list	*next;
}	t_list;

/* ============================================================================
** Character Classification
** ========================================================================= */
int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isalnum(char c);
int		ft_isascii(char c);
int		ft_isprint(char c);
int		ft_isspace(char c);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* ============================================================================
** String Functions
** ========================================================================= */
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *lil, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char trim_char);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);

/* ============================================================================
** String Array Utilities
** ========================================================================= */
int		ft_strslen(char **strs);
size_t	ft_strilen(int *str);
size_t	ft_strsilen(int **str);

/* ============================================================================
** Memory Functions
** ========================================================================= */
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmeb, size_t size);

/* ============================================================================
** Conversion
** ========================================================================= */
int			ft_atoi(const char *str);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);

/* ============================================================================
** File Descriptor Output
** ========================================================================= */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* ============================================================================
** Array Utilities
** ========================================================================= */
int		ft_arrlen(char **arr);
int		ft_min(int a, int b);
int		ft_max(int a, int b);

/* ============================================================================
** Other Utilities
** ========================================================================= */
void	ft_putperror(char *msg, int exit_code);
void	ft_freearr(char **arr);
char	*get_next_line(int fd);

#endif