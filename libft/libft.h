/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:44:15 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:50:00 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

size_t		ft_strlen(const char *s);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_is_space(char c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define READ 1
# define NO 0
# define ERROR -1

char		*get_next_line(int fd);
int			read_check(char *store);
char		*read_loop(char **store, ssize_t *store_size, int fd, char *buff);
char		*get_one_line(char **store, ssize_t *st_size);
char		*line_store(char **store, ssize_t *st_size, char *buf,
				ssize_t rd_size);
char		*make_oneline(char **store, ssize_t *st_size);
void		trim_store(char **store, ssize_t *st_size, ssize_t i, ssize_t j);

#endif