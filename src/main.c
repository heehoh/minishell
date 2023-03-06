/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/06 20:51:58 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "process.h"

void	create_process(t_cmd *cmd, t_env *env);

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
	int		j;

	get_env_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			builtin_exit(0);
		if (input[0] == '\0')
			hamsu();
		add_history(input);
		cmd = parse_input(input);
		create_process(cmd, g_global);
		free(input);
	}
}
/*널문자만 들어올 경우 main에서 처리"
input[0] ='\0'
cc src/main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c -lreadline*/