/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/22 15:16:16 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "process.h"

void	set_terminal_print_on(void);

void	exit_minishell(t_env *env, t_current *current)
{
	t_env	*tem;

	free(current->path);
	while (env)
	{
		tem = env->next;
		free(env->var);
		free(env);
		env = tem;
	}
	write(1, "exit\n", 5);
	set_terminal_print_on();
	exit(0);
}

int	input_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		++i;
	if (input[i] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

void	minishell_loop(t_env *env_list, t_current *current)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		input = readline(MINISHELL);
		if (input == NULL)
			exit_minishell(env_list, current);
		if (input_check(input))
			continue ;
		add_history(input);
		if (syntax_error(input, 0, 0))
		{
			current->status = 258;
			free(input);
			continue ;
		}
		cmd = parse_input(input, env_list, current->status);
		current->status = create_process(cmd, env_list, current);
		cmd_clear(cmd);
		rl_on_new_line();
	}
}

int	main(int argc, __attribute__((unused))char **argv, char **env)
{
	t_env		*env_list;
	t_current	current;

	if (argc != 1 && printf("Error: argument\n"))
		return (1);
	init_setting(env, &env_list, &current);
	minishell_loop(env_list, &current);
}
