/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:57:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/08 14:16:31 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int g_status = 100;

int	num_env_exit(int *count)
{
	int		len;
	char	*num;

	num = ft_itoa(g_status);
	if (num == NULL)
		error_malloc();
	len = ft_strlen(num);
	*count += len;
	free(num);
	return (len + 1);
}

int	put_env_exit(char *change, int *count)
{
	int		i;
	char	*num;

	num = ft_itoa(g_status);
	if (num == NULL)
		error_malloc();
	i = 0;
	while (num[i])
	{
		change[*count] = num[i];
		++(*count);
		++i;
	}
	free(num);
	return (i + 1);
}
