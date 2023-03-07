/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:25:25 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 21:20:00 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int	g_status;

t_cmd	*parse_input(char *str, t_env *env);
t_file	*parse_file(char *sep_pipe);
char	**parse_cmd_option(char *sep_pipe);
void	replace_util(char **str, t_env *env);
t_env	*get_env_list(char **env);
void	is_cmd_or_file(char **sep_pipe, int *flag);
int		flag_quote(char *sep_pipe, int *quote_flag);
void	cmd_clear(t_cmd *cmd);

int		syntax_error(char *input);
void	error_malloc(void);
void	error_pipe(void);
void	error_fork(void);
void	error_open(char *name);
void	error_access(char *cmd);


#endif