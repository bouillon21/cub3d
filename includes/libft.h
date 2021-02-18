/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:22 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/18 16:58:44 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(const char *s);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_lstsize(t_list *lst);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t number, size_t size);
void				*ft_memccpy(void *destptr, const void *srcptr,
								int c, size_t num);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memchr(void *memptr, int val, size_t num);
void				*ft_memcpy(void *destptr, const void *srcptr, size_t num);
void				*ft_memmove(void *destptr, const void *srcptr, size_t n);
void				*ft_memset(void *memptr, int val, size_t num);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
char				*ft_strchr(const char *str, int symbol);
char				*ft_strdup(char *src);
char				*ft_strnstr(const char *s, const char *need, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strrchr(const char *str, int symbol);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *destptr, const char *srcptr, size_t size);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));
#endif
