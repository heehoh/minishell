/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:12:54 by hujeong           #+#    #+#             */
/*   Updated: 2023/01/26 19:09:25 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*line_store(char **store, ssize_t *st_size, char *buff, ssize_t rd_size)
{
	ssize_t	i;
	char	*new_store;	

	new_store = (char *)malloc(*st_size + rd_size + 1);
	if (new_store == NULL)
	{
		free(*store);
		*store = NULL;
		*st_size = 0;
		return (NULL);
	}
	i = -1;
	while (++i < *st_size)
		new_store[i] = (*store)[i];
	--i;
	while (++i < *st_size + rd_size)
		new_store[i] = buff[i - *st_size];
	*st_size += rd_size;
	new_store[*st_size] = '\0';
	free(*store);
	return (new_store);
}

char	*make_oneline(char **store, ssize_t *st_size)
{
	ssize_t	i;
	ssize_t	j;
	char	*one_line;

	i = -1;
	while (++i < *st_size)
		if ((*store)[i] == '\n')
			break ;
	if ((*store)[i] == '\n')
		++i;
	one_line = (char *)malloc(i + 1);
	if (one_line == NULL)
	{
		free(*store);
		*store = NULL;
		*st_size = 0;
		return (NULL);
	}
	j = -1;
	while (++j < i)
		one_line[j] = (*store)[j];
	one_line[i] = '\0';
	return (one_line);
}

void	trim_store(char **store, ssize_t *st_size, ssize_t i, ssize_t j)
{
	char	*new_store;

	while (++i < *st_size)
		if ((*store)[i] == '\n')
			break ;
	if ((*store)[i] == '\n')
		++i;
	new_store = (char *)malloc(*st_size - i + 1);
	if (new_store == NULL || i == *st_size)
	{
		free(*store);
		free(new_store);
		*store = NULL;
		*st_size = 0;
		return ;
	}
	while (++j + i < *st_size)
		new_store[j] = (*store)[j + i];
	new_store[j] = '\0';
	*st_size = j;
	free(*store);
	*store = new_store;
}
