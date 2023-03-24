/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:23:35 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/24 13:38:38 by migo             ###   ########.fr       */
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

int	not_valid_unset(char *str)
{
	if (str[0] == '_')
		return (1);
	write(2, "unset: ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}
