/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:05:38 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/24 16:01:36 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_word(char const *s, char c, int word, int i)
{
	char	tem;

	while (s[i])
	{
		if (s[i] == c)
			++i;
		else if (s[i] == '\'' || s[i] == '\"')
		{
			tem = s[i];
			while (s[i] && s[++i] != tem)
				;
			++word;
			if (s[i] == tem)
				++i;
		}
		else
		{
			while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
				++i;
			if (s[i] == '\'' || s[i] == '\"')
				continue ;
			++word;
		}
	}
	return (word);
}

static void	save_str_util(char *str, int *i)
{
	char	tem;

	tem = str[*i];
	while (str[*i] && str[++(*i)] != tem)
		;
	if (str[*i])
		++(*i);
}

static char	*save_str(char *str, char c, int i)
{
	char	*strs;
	char	tem;

	while (*str == c)
		++str;
	if (str[i] == '\'' || str[i] == '\"')
		save_str_util(str, &i);
	else
	{
		while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
			++i;
		if (str[i] == '\"' || str[i] == '\'')
			save_str_util(str, &i);
	}
	strs = (char *)malloc(sizeof(char) * i + 1);
	if (strs == NULL)
		return (NULL);
	strs[i] = '\0';
	while (--i >= 0)
		strs[i] = str[i];
	return (strs);
}

static char	*move_str(char *str, char c)
{
	int		i;
	char	tem;

	i = 0;
	while (str[i] == c)
		++i;
	if (str[i] == '\'' || str[i] == '\"')
		save_str_util(str, &i);
	else
	{
		while (str[i] != c && str[i] != '\'' && str[i] != '\"')
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			save_str_util(str, &i);
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
	word = count_word(str, c, 0, 0);
	strs = (char **)malloc(sizeof(char *) * (word + 1));
	if (strs == 0)
		return (0);
	i = -1;
	while (++i < word)
	{		
		strs[i] = save_str(str, c, 0);
		if (strs[i] == NULL)
		{
			while (--i >= 0)
				free(strs[i]);
			free(strs);
			return (0);
		}
		str = move_str(str, c);
	}
	strs[i] = NULL;
	return (strs);
}
