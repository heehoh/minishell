/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:57:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/09 18:25:14 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int	num_env_exit(int *count, int status)
{
	int		len;
	char	*num;

	num = ft_itoa(status);
	if (num == NULL)
		error_malloc();
	len = ft_strlen(num);
	*count += len;
	free(num);
	return (2);
}

int	put_env_exit(char *change, int *count, int status)
{
	int		i;
	char	*num;

	num = ft_itoa(status);
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
	return (2);
}
