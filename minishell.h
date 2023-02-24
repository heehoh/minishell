/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:26:04 by migo              #+#    #+#             */
/*   Updated: 2023/02/24 14:58:40 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>

typedef struct s_list
{
	char	*env;
	struct s_list *next;
}	t_list;

typedef struct s_file
{
	char	*file;
	int		redirection;
}	t_file;

typedef struct s_cmd
{
	t_file	*file;
	char	**option;
	struct s_cmd *next;
}	t_cmd;


#endif

// cmd1 | cmd2 | cmd3
// 1       1     0
// dup2(fd[1], 1) dup2(fd[0], 0) dup2(fd[1], 1) dup2(fd[0], 0)