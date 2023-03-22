/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:25:25 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/22 14:48:21 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

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

typedef struct s_current
{
	char				*path;
	int					status;
}	t_current;

# define CMDFLAG 0
# define FILEFLAG 1
# define INITERR "shell-init: error retrieving current directory: \
getcwd: cannot access parent directories"
# define MINISHELL "\033[32mminishell$ \033[0m"

void	init_setting(char **env, t_env **env_list, t_current *current);
t_cmd	*parse_input(char *str, t_env *env, int status);
t_file	*parse_file(char *sep_pipe);
char	**parse_cmd_option(char *sep_pipe);
void	replace_env(char **sep_pipe, t_env *env, int status);
void	delete_quote(t_cmd *cmd);
t_env	*get_env_list(char **env);
char	**get_env_array(t_env *env);
void	is_cmd_or_file(char **sep_pipe, int *flag);
int		flag_quote(char *sep_pipe, int *quote_flag);
void	cmd_clear(t_cmd *cmd);
void	str_array_clear(char **str);

int		num_env_exit(int *count, int status);
int		put_env_exit(char *change, int *count, int status);

int		is_builtin(char *command);
int		builtin_process(t_cmd *cmd, t_env *env, int count, t_current *current);

int		syntax_error(char *input, int quote_flag, int cmd_flag);
void	error_malloc(void);
void	error_pipe(void);
void	error_fork(void);
void	error_open(char *name);
void	error_access(char *cmd);
void	error_cmd_not_found(char *cmd);

int		builtin_cd(t_cmd *cmd, t_env *tmp, t_current *current);
int		builtin_echo(t_cmd *cmd);
int		builtin_env(t_cmd *cmd, t_env *tmp);
void	builtin_exit(t_cmd *cmd, int count);
int		builtin_export(t_cmd *cmd, t_env *env, int i, int j);
int		builtin_pwd(t_current *current);
int		builtin_unset(t_cmd *cmd, t_env *env, int i, int j);

#endif