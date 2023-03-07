/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:14:19 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/06 16:48:31 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strjoin_utils(char *s1, char const *s2, size_t *len1, size_t *len2)
{
	*len1 = ft_strlen(s1);
	*len2 = ft_strlen(s2);
	return ((char *)malloc(*len1 + *len2 + 1));
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*str;

	str = strjoin_utils(s1, s2, &len1, &len2);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		++i;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		++i;
	}
	str[i] = '\0';
	return (str);
}
