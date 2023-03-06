/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:26:04 by migo              #+#    #+#             */
/*   Updated: 2023/03/04 14:49:25 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	char	*name;
	int		redirection;
}	t_file;

typedef struct s_cmd
{
	t_file			*file;
	char			**option;
	struct s_cmd	*next;
}	t_cmd;

# define CMDFLAG 0
# define FILEFLAG 1

t_env	*g_global;

t_cmd	*parse_input(char *str);
t_file	*parse_file(char *sep_pipe);
char	**parse_cmd_option(char *sep_pipe);
void	replace_util(char **str, t_env *env);
void	get_env_list(char **env);
void	is_cmd_or_file(char **sep_pipe, int *flag);
int		flag_quote(char *sep_pipe, int *quote_flag);

#endif

// cmd1 | cmd2 | cmd3
// 1       1     0
// dup2(fd[1], 1) dup2(fd[0], 0) dup2(fd[1], 1) dup2(fd[0], 0)
// env를 전역변수로 처리?
