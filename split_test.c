/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:17:58 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/26 16:52:13 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	**ft_split(char *str, char c);

int	main(int argc, char *argv[])
{
	char	**strs;
	int		i;

	if (argc != 2)
		return (0);

	strs = ft_split(argv[1], '|');
	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		++i;
	}
	printf("%d\n", i);
	return (0);
}
