/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:23:35 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 14:28:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/libft.h"

int	no_file_directory(char *str)
{
	write(2, "minishell: cd: ", 15);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	return (0);
}

int	no_directory(char *str)
{
	write(2, "minishell: cd: ", 15);
	write(2, str, ft_strlen(str));
	write(2, ": Not a directory\n", 18);
	return (0);
}
