/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:10:45 by hujeong           #+#    #+#             */
/*   Updated: 2023/01/26 19:09:27 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		*store;
	static ssize_t	store_size;
	char			buff[BUFFER_SIZE];
	char			*one_line;
	int				check;

	check = read_check(store);
	if (check == READ)
		one_line = read_loop(&store, &store_size, fd, buff);
	else
		one_line = get_one_line(&store, &store_size);
	return (one_line);
}

int	read_check(char	*store)
{
	size_t	i;

	if (store == NULL)
		return (READ);
	i = -1;
	while (store[++i])
		if (store[i] == '\n')
			return (NO);
	return (READ);
}

char	*read_loop(char **store, ssize_t *store_size, int fd, char *buff)
{
	ssize_t	read_size;
	ssize_t	i;

	while (1)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0 || (*store_size == 0 && read_size == 0))
		{
			free(*store);
			*store = NULL;
			*store_size = 0;
			return (NULL);
		}
		*store = line_store(store, store_size, buff, read_size);
		if (*store == NULL)
			return (NULL);
		i = -1;
		while (++i < read_size)
			if (buff[i] == '\n')
				break ;
		if (i == read_size && read_size == BUFFER_SIZE)
			continue ;
		return (get_one_line(store, store_size));
	}
}

char	*get_one_line(char **store, ssize_t *store_size)
{
	char	*one_line;

	one_line = make_oneline(store, store_size);
	if (one_line == NULL)
		return (NULL);
	trim_store(store, store_size, -1, -1);
	return (one_line);
}
