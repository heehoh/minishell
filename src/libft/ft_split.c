/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:05:38 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/26 16:51:53 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_word(char *s, char c, int word, char flag)
{
	char	quote;

	while (*s)
	{
		if (flag == 1 && *s == c)
			++s;
		else
		{
			while (*s && (*s != c || flag == -1))
			{
				if (flag == 1 && (*s == '\'' || *s == '\"'))
				{
					quote = *s;
					flag *= -1;
				}
				else if (flag == -1 && *s == quote)
					flag *= -1;
				++s;
			}
			++word;
		}
	}
	return (word);
}

static char	*save_str(char *str, char c, int i, char flag)
{
	char	*strs;
	char	quote;

	while (*str == c)
		++str;
	while (str[i] && (str[i] != c || flag == -1))
	{
		if (flag == 1 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			flag *= -1;
		}
		else if (flag == -1 && str[i] == quote)
			flag *= -1;
		++i;
	}
	strs = (char *)malloc(sizeof(char) * i + 1);
	if (strs == NULL)
		return (NULL);
	strs[i] = '\0';
	while (--i >= 0)
		strs[i] = str[i];
	return (strs);
}

static char	*move_str(char *str, char c, char flag)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] == c)
		++i;
	while (str[i] && (str[i] != c || flag == -1))
	{
		if (flag == 1 && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			flag *= -1;
		}
		else if (flag == -1 && str[i] == quote)
			flag *= -1;
		++i;
	}
	return (&str[i]);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*str;
	int		word;
	int		i;

	str = (char *)s;
	word = count_word(str, c, 0, 1);
	strs = (char **)malloc(sizeof(char *) * (word + 1));
	if (strs == 0)
		return (0);
	i = -1;
	while (++i < word)
	{		
		strs[i] = save_str(str, c, 0, 1);
		if (strs[i] == NULL)
		{
			while (--i >= 0)
				free(strs[i]);
			free(strs);
			return (0);
		}
		str = move_str(str, c, 1);
	}
	strs[i] = NULL;
	return (strs);
}
