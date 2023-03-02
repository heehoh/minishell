/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/02 17:14:39 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

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
		{
			printf(" exit\n");
			return (0);
		}
		add_history(input);
		cmd = parse_input(input);
		j = 1;
		while (cmd)
		{
		int i = 0;
		while (cmd->option[i])
		{
			printf("%d pipe -> option : %s\n",j, cmd->option[i]);
			i++;
		}
		i = 0;
		while (cmd->file[i].redirection != 0)
		{
			printf("redirection : %d\n", cmd->file[i].redirection);
			printf("file : %s\n", cmd->file[i].name);
			i++;
		}
		cmd = cmd->next;
		++j;
		}
		free(input);
	}
}
/*널문자만 들어올 경우 main에서 처리"
cc src/main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c -lreadline*/