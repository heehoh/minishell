/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:29:36 by migo              #+#    #+#             */
/*   Updated: 2023/01/31 15:08:24 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	reduce(char const *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] == charset)
		i++;
	return (i);
}

int	mkshare1(char const *str, char charset)
{
	int	i;
	int	j;
	int	m;

	i = reduce(str, charset);
	m = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] != charset && str[i + j])
		{
			if (str[i + j] == '\'' || str[i + j] == '\"')
				j = quote(str, i + j) - i;
			j++;
		}
		m++;
		while (str[i + j] == charset && str[i + j])
			j++;
		i = i + j;
	}
	return (m);
}

int	mkshare2(char const *str, char *share[], char charset)
{
	int	i;
	int	j;
	int	m;

	i = reduce(str, charset);
	m = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] != charset && str[i + j])
		{
			if (str[i + j] == '\'' || str[i + j] == '\"')
				j = quote(str, i + j) - i;
			j++;
		}
		share[m] = (char *)malloc(sizeof(char) * (j + 1));
		if (share[m] == 0)
			return (0);
		m++;
		while (str[i + j] == charset && str[i + j])
			j++;
		i = i + j;
	}
	return (1);
}

void	mkshare3(char const *str, char *share[], char charset)
{
	int	i;
	int	j;
	int	m;

	i = 0;
	m = 0;
	while (str[i] == charset)
		i++;
	while (str[i])
	{
		j = 0;
		while (str[i + j] != charset && str[i + j])
		{
			if (str[i + j] == '\'' || str[i + j] == '\"')
				j = quote1(str, i + j, share, m) - i;
			share[m][j] = str[i + j];
			j++;
		}
		share[m][j] = '\0';
		m++;
		while (str[i + j] == charset && str[i + j])
			j++;
		i = i + j;
	}
}

char	**ft_split(char const *str, char charset, int a)
{
	int		i;
	char	**share;

	if (str[0] == '\0')
	{
		share = (char **)malloc(sizeof(char *) * 1);
		if (share == 0)
			return (0);
		share[0] = 0;
		return (share);
	}
	i = mkshare1(str, charset);
	share = malloc(sizeof(char *) * (i + 1 + a));
	if (share == 0)
		return (0);
	if (mkshare2(str, share, charset) == 0)
	{
		free (share);
		return (0);
	}
	mkshare3(str, share, charset);
	share[i + a] = 0;
	share[i] = 0;
	return (share);
}
