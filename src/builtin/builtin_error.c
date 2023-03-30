/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:23:35 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/30 11:50:28 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	not_have_path(void)
{
	write(2, "chdir: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories", 41);
	write(2, ": No such file or directory\n", 28);
}
