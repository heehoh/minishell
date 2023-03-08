/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/08 13:52:45 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "process.h"

int	create_process(t_cmd *cmd, t_env *env);

int	main(int argc, __attribute__((unused))char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
	t_env	*env_list;
	int		g_status;

	if (argc != 1)
		return (1);
	env_list = get_env_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (input[0] == '\0')
			exit(0);
		add_history(input);
		g_status = syntax_error(input, 0, 0);
		if (g_status == 258)
			continue ;
		cmd = parse_input(input, env_list);
		g_status = create_process(cmd, env_list);
		cmd_clear(cmd);
	}
}
