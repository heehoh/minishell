/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/04/03 09:11:42 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "process.h"

int		g_status;
void	set_terminal_print_on(void);

void	exit_minishell(t_env *env, t_current *current, int num)
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
	set_terminal_print_on();
	rl_clear_history();
	exit(num);
}

int	input_check(char *input)
{
	int	i;

	i = 0;
	while (ft_is_space(input[i]))
		++i;
	if (input[i] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

void	minishell_loop(t_current *current)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		input = readline(MINISHELL);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			exit_minishell(current->env, current, g_status);
		}
		if (input_check(input))
			continue ;
		add_history(input);
		if (syntax_error(input, 0, 0))
		{
			g_status = 258;
			free(input);
			continue ;
		}
		cmd = parse_input(input, current->env, g_status);
		g_status = create_process(cmd, current->env, current);
		cmd_clear(cmd);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_current	current;

	g_status = 0;
	if ((argc != 1 || argv[0] == NULL) && printf("Error: argument\n"))
		return (1);
	init_setting(env, &current);
	minishell_loop(&current);
}
