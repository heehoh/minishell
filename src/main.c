/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/10 10:59:23 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "process.h"

void	exit_minishell(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

int	free_input(char *input)
{
	free(input);
	return (1);
}

void	init_setting(char **env, t_env **env_list, t_current *current)
{
	*env_list = get_env_list(env);
	current->path = (char *)malloc(sizeof(char) * 4096);
	if (getcwd(current->path, 4096))
	{
		perror(INITERR);
		current->path[0] = '\0';
	}
	current->status = 0;
}

int	main(int argc, __attribute__((unused))char **argv, char **env)
{
	char		*input;
	t_cmd		*cmd;
	t_env		*env_list;
	t_current	current;

	if (argc != 1 && printf("Error: argument\n"))
		return (1);
	init_setting(env, &env_list, &current);
	while (1)
	{
		input = readline(MINISHELL);
		if (input == NULL)
			exit_minishell();
		if (input[0] == '\0' && free_input(input))
			continue ;
		add_history(input);
		current.status = syntax_error(input, 0, 0);
		if (current.status == 258 && free_input(input))
			continue ;
		cmd = parse_input(input, env_list, current.status);
		current.status = create_process(cmd, env_list, &current);
		cmd_clear(cmd);
	}
}
